#include "stdafx.h"
#include "ButtonLobbySelectCreateLobbyCommand.h"

void app::cmnd::ButtonLobbySelectCreateLobbyCommand::execute()
{
	if (m_client.hasInit())
	{
		constexpr auto PACKET_TYPE = app::net::PacketType::LOBBY_CREATE;
		if (!m_client.send(PACKET_TYPE))
		{
			this->output("Failed to 'Lobby Create' packet");
		}
	}
}
