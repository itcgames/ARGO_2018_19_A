#include "stdafx.h"
#include "ButtonLobbySelectRefreshCommand.h"
#include "shared/network/Lobby.h"
#include "factories/entities/LobbyDisplayFactory.h"
#include "components/Layer.h"
#include "systems/RenderSystem.h"

app::cmnd::ButtonLobbySelectRefreshCommand::ButtonLobbySelectRefreshCommand(std::forward_list<app::Entity> entities, app::sce::SceneType & sceneControl)
	: BaseMultiplayerCommand()
	, m_entities(entities)
	, m_sceneControl(sceneControl)
{
}

void app::cmnd::ButtonLobbySelectRefreshCommand::execute()
{
	if (m_client.hasInit())
	{
		constexpr auto PACKET_TYPE = app::net::PacketType::LOBBY_GET_ALL;
		if (!m_client.send(PACKET_TYPE))
		{
			this->output("Sending 'get all lobby' packet type failed");
			return;
		}
		this->output("Sending 'get all lobby' packet type successfull");
		auto const & lobbies = m_client.getLobbies();
		while (!m_client.checkSocket());
		if (!m_client.processPacket(PACKET_TYPE))
		{
			this->output("Receival of 'Lobbies' failed");
			return;
		}
		else
		{
			m_registry.construction<comp::Layer>().disconnect<&app::sys::RenderSystem::onLayerConstruction>();
			m_registry.destruction<comp::Layer>().disconnect<&app::sys::RenderSystem::onLayerConstruction>();
			auto params = par::LobbyDisplayFactoryParameters();
			params.position = math::Vector2f{ -450.0f, -300.0f };
			params.lobbies = lobbies;
			params.entities.insert(params.entities.end(), m_entities.begin(), m_entities.end());
			auto entities = fact::LobbyDisplayFactory(params, m_sceneControl).create();
			app::sys::RenderSystem::onLayerConstruction(m_registry, 0);
			m_registry.construction<comp::Layer>().connect<&app::sys::RenderSystem::onLayerConstruction>();
			m_registry.destruction<comp::Layer>().connect<&app::sys::RenderSystem::onLayerConstruction>();
		}
		this->output({ "Receival of [", lobbies.size(), "]'Lobbies' successfull" });
	}
}
