#include "stdafx.h"
#include "ButtonLobbySelectCreateLobbyCommand.h"
#include "ButtonLobbySelectCommand.h"

app::cmnd::ButtonLobbySelectCreateLobbyCommand::ButtonLobbySelectCreateLobbyCommand(
	  std::string const & userName
	, app::sce::SceneType & sceneControl
)
	: BaseMultiplayerCommand()
	, m_userName(userName)
	, m_sceneControl(sceneControl)
{
}

void app::cmnd::ButtonLobbySelectCreateLobbyCommand::execute()
{
	if (m_client.hasInit())
	{
		constexpr auto PACKET_TYPE = app::net::PacketType::LOBBY_CREATE;
		if (!m_client.send(PACKET_TYPE))
		{
			this->output("Failed to 'Lobby Create' packet");
		}
		if (!m_client.send(m_userName))
		{
			this->output({ "Failed to send username '", m_userName, "'" });
		}
		while (!m_client.checkSocket());
		auto packetType = app::net::PacketType::UNKNOWN;
		if (!m_client.get(packetType))
		{
			this->output("Failed to process next packet");
		}
		if (!m_client.processPacket(packetType))
		{
			this->output({ "Failed to receive lobby" });
		}
		constexpr auto IS_HOST = true;
		std::make_unique<cmnd::ButtonLobbySelectCommand>(m_client.getLobbies().back(), IS_HOST, m_sceneControl)->execute();
	}
}
