#include "stdafx.h"
#include "NetworkSystem.h"
#include "singletons/ClientSingleton.h"
#include "commands/buttons/ButtonLobbySelectCommand.h"
#include "commands/buttons/ButtonLobbySelectRefreshCommand.h"
#include "factories/entities/LobbyDisplayFactory.h"

#include "components/LobbyDisplay.h"
#include "components/Widget.h"
#include "components/Location.h"
#include "components/Ghost.h"
#include "components/Layer.h"
#include "components/Commandable.h"
#include "systems/RenderSystem.h"
#include "tags/LobbyTag.h"

app::sys::NetworkSystem::NetworkSystem(app::sce::SceneType & sceneControl)
	: BaseSystem()
	, m_client(app::sin::Client::get())
	, m_packetType()
	, m_sceneControl(sceneControl)
{
}

void app::sys::NetworkSystem::update(app::time::seconds const & dt)
{
	if (m_client.hasInit() && m_client.checkSocket())
	{
		m_packetType = app::net::PacketType::UNKNOWN;
		if (!m_client.get(m_packetType))
		{
			this->output("Failed to retrieve packet type");
		}
		if (m_client.processPacket(m_packetType))
		{
			this->output("Processed packet successfully");
			switch (m_sceneControl)
			{
				case app::sce::SceneType::Lobby:
					this->handlePacketLobbyIJoined();
					this->handlePacketLobbyReady();
					break;
				case app::sce::SceneType::LobbySelect:
					this->handlePacketLobbyWasCreated();
					this->handlePacketLobbyWasJoined();
					this->handlePacketLobbyIJoined();
					this->handlePacketLobbyReady();
					break;
				case app::sce::SceneType::MultiplayerLevel:
					this->handlePacketLevelNewPlayerInfo();
					break;
				default:
					break;
			}
		}
		else
		{
			this->output("Failed to process packet");
		}
	}
}

void app::sys::NetworkSystem::output(std::string const & msg) const
{
	if constexpr (s_DEBUG_MODE)
	{
		app::Console::writeLine(msg);
	}
}

void app::sys::NetworkSystem::output(std::initializer_list<app::Console::Variant> const & msgs) const
{
	if constexpr (s_DEBUG_MODE)
	{
		app::Console::writeLine(msgs);
	}
}

void app::sys::NetworkSystem::handlePacketLobbyWasCreated()
{
	if (m_packetType != app::net::PacketType::LOBBY_WAS_CREATED) { return; }

	auto buttonView = m_registry.view<comp::Widget>();
	auto lobbyDisplayView = m_registry.view<comp::Widget, comp::LobbyDisplay>();
	auto entities = std::vector<app::Entity>();
	for (auto const & entity : buttonView)
	{
		if (!lobbyDisplayView.contains(entity)) { entities.push_back(entity); }
	}

	auto const & lobbies = m_client.getLobbies();
	auto params = par::LobbyDisplayFactoryParameters();
	params.position = math::Vector2f{ -450.0f, -300.0f };
	params.lobbies = lobbies;
	params.entities.insert(params.entities.end(), entities.begin(), entities.end());
	entities = fact::LobbyDisplayFactory(params, m_sceneControl).create();
}

void app::sys::NetworkSystem::handlePacketLobbyWasJoined()
{
	if (m_packetType != app::net::PacketType::LOBBY_JOINED) { return; }

	auto buttonView = m_registry.view<comp::Widget>();
	auto lobbyDisplayView = m_registry.view<comp::Widget, comp::LobbyDisplay>();
	auto entities = std::vector<app::Entity>();
	for (auto const & entity : buttonView)
	{
		if (!lobbyDisplayView.contains(entity)) { entities.push_back(entity); }
	}
	
	{
		auto refreshEntities = std::forward_list<app::Entity>();
		refreshEntities.insert_after(refreshEntities.before_begin(), entities.begin(), entities.end());

		auto entity = m_registry.create();

		auto commandable = comp::Commandable();
		commandable.list.emplace_front(std::make_unique<cmnd::ButtonLobbySelectRefreshCommand>(refreshEntities, m_sceneControl));
		m_registry.assign<decltype(commandable)>(entity, std::move(commandable));
	}
}

void app::sys::NetworkSystem::handlePacketLobbyIJoined()
{
	if (m_packetType != app::net::PacketType::LOBBY_JOINED_MY) { return; }
	this->updateLobbyTag();
}

void app::sys::NetworkSystem::handlePacketLevelNewPlayerInfo()
{
	if (m_packetType != app::net::PacketType::LEVEL_NEW_PLAYER_INFO) { return; }

	auto playerId = std::int32_t();
	if (!m_client.get(playerId)) {}

	auto newPosition = math::Vector2f();
	if (!m_client.get(newPosition)) {}

	auto ghostView = m_registry.view<comp::Ghost, comp::Location>();
	ghostView.each([&, this](app::Entity const entity, comp::Ghost & ghost, comp::Location & location)
	{
		if (ghost.id == playerId) { return; }
		location.position = newPosition;
	});
}

void app::sys::NetworkSystem::handlePacketLobbyReady()
{
	if (m_packetType != app::net::PacketType::LOBBY_READY) { return; }

	m_sceneControl = app::sce::SceneType::MultiplayerLevel;
}

void app::sys::NetworkSystem::updateLobbyTag()
{
	auto & lobbyTag = m_registry.get<tag::Lobby>();
	auto const predicate =
		[&](app::net::Lobby const & lobby) { return lobby.getId() == lobbyTag.id; };
	auto & lobbies = m_client.getLobbies();
	if (auto const & result = std::find_if(lobbies.begin(), lobbies.end(), predicate); result != lobbies.end())
	{
		auto & lobby = *result;
		lobbyTag.name = lobby.getName();
		lobbyTag.players = lobby.getPlayers();
		lobbyTag.name = lobby.getName();
	}
	else
	{
		throw std::exception("Lobby Tag contains invalid lobby id");
	}
}
