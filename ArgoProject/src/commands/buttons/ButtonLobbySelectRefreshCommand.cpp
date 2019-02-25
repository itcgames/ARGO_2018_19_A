#include "stdafx.h"
#include "ButtonLobbySelectRefreshCommand.h"
#include "shared/network/Lobby.h"
#include "factories/entities/LobbyDisplayFactory.h"

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
			auto params = par::LobbyDisplayFactoryParameters();
			params.position = math::Vector2f{ -450.0f, -300.0f };
			params.lobbies = lobbies;
			params.entities.insert(params.entities.end(), m_entities.begin(), m_entities.end());
			fact::LobbyDisplayFactory(params, m_sceneControl).create();
		}
		this->output({ "Receival of [", std::to_string(lobbies.size()), "]'Lobbies' successfull" });
	}
}
