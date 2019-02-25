#include "stdafx.h"
#include "ButtonLobbySelectCommand.h"
#include "components/Destroy.h"
#include "tags/LobbyTag.h"

app::cmnd::ButtonLobbySelectCommand::ButtonLobbySelectCommand(app::net::Lobby const lobby, app::sce::SceneType & sceneControl)
	: BaseMultiplayerCommand()
	, m_lobby(lobby)
	, m_sceneControl(sceneControl)
{
}

void app::cmnd::ButtonLobbySelectCommand::execute()
{
	if constexpr (s_DEBUG_MODE)
	{
		app::Console::writeLine({ "Selected lobby '", m_lobby.getName(), "'" });
	}
	if (m_sceneControl != app::sce::SceneType::Lobby)
	{
		m_registry.each([this](app::Entity const entity) { m_registry.accommodate<comp::Destroy>(entity); });
		m_sceneControl = app::sce::SceneType::Lobby;
		auto lobbyTag = tag::Lobby();
		lobbyTag.name = m_lobby.getName();
		lobbyTag.isHost = true;
		for (std::int32_t i = 0; i < lobbyTag.players.size(); ++i)
		{
			if (i >= m_lobby.getPlayers().size()) { break; }

			auto & player = lobbyTag.players.at(i);
			auto const & playerName = this->getPlayerName(i);
			player = playerName;
		}
		m_registry.accommodate<tag::Lobby>(m_registry.create(), std::move(lobbyTag));
	}
}

std::string const & app::cmnd::ButtonLobbySelectCommand::getPlayerName(std::int32_t const & index) const
{
	auto itt = m_lobby.getPlayers().cbegin();
	for (std::size_t i = 0; i < index; ++i) { ++itt; }
	return itt->second;
}
