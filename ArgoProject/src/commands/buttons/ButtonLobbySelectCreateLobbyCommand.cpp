#include "stdafx.h"
#include "ButtonLobbySelectCreateLobbyCommand.h"

app::cmnd::ButtonLobbySelectCreateLobbyCommand::ButtonLobbySelectCreateLobbyCommand(
	std::string const & userName
)
	: BaseMultiplayerCommand()
	, m_userName(userName)
{
}

void app::cmnd::ButtonLobbySelectCreateLobbyCommand::execute()
{
	return;
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

	}
}
