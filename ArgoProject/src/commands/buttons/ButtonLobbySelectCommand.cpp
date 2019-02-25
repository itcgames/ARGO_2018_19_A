#include "stdafx.h"
#include "ButtonLobbySelectCommand.h"
#include "components/LobbyDisplay.h"

app::cmnd::ButtonLobbySelectCommand::ButtonLobbySelectCommand(app::net::Lobby const lobby)
	: BaseMultiplayerCommand()
	, m_lobby(lobby)
{
}

void app::cmnd::ButtonLobbySelectCommand::execute()
{
	if constexpr (s_DEBUG_MODE)
	{
		app::Console::writeLine({ "Selected lobby '", m_lobby.getName(), "'" });
	}
}
