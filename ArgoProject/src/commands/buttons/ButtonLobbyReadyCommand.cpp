#include "stdafx.h"
#include "ButtonLobbyReadyCommand.h"
#include "shared/network/Lobby.h"
#include "components/Layer.h"
#include "systems/RenderSystem.h"

app::cmnd::ButtonLobbyReadyCommand::ButtonLobbyReadyCommand(std::forward_list<app::Entity> entities, app::sce::SceneType & sceneControl)
	: BaseMultiplayerCommand()
	, m_entities(entities)
	, m_sceneControl(sceneControl)
{
}

void app::cmnd::ButtonLobbyReadyCommand::execute()
{
	if (m_client.hasInit())
	{
		constexpr auto PACKET_TYPE = app::net::PacketType::LOBBY_READY;
		if (!m_client.send(PACKET_TYPE))
		{
			this->output("Sending 'lobby ready' packet type failed");
			return;
		}
		this->output("Sending 'lobby ready' packet type successfull");
	}
}
