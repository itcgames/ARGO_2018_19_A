#include "stdafx.h"
#include "NetworkSystem.h"
#include "singletons/ClientSingleton.h"
#include "commands/buttons/ButtonLobbySelectRefreshCommand.h"
#include "commands/buttons/ButtonLobbySelectCommand.h"

#include "components/Widget.h"
#include "components/Location.h"
#include "components/Ghost.h"
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
			if (m_packetType == app::net::PacketType::LOBBY_WAS_CREATED && m_sceneControl == app::sce::SceneType::LobbySelect)
			{
				auto buttonView = m_registry.view<comp::Widget>();
				auto entities = std::forward_list<app::Entity>();
				for (auto const & entity : buttonView) { entities.push_front(entity); }
				std::make_unique<cmnd::ButtonLobbySelectRefreshCommand>(entities, m_sceneControl)->execute();
			}
			else if (m_sceneControl == app::sce::SceneType::MultiplayerLevel)
			{
				if (m_packetType == app::net::PacketType::LEVEL_NEW_PLAYER_INFO)
				{
					auto playerId = std::int32_t();
					if (!m_client.get(playerId)) {}

					auto newPosition = math::Vector2f();
					if (!m_client.get(newPosition)) { }

					auto ghostView = m_registry.view<comp::Ghost, comp::Location>();
					ghostView.each([&, this](app::Entity const entity, comp::Ghost & ghost, comp::Location & location)
					{
						if (ghost.id != playerId) { return; }
							location.position = newPosition;
					});
				}
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
