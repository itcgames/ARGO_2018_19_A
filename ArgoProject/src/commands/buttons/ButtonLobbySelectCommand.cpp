#include "stdafx.h"
#include "ButtonLobbySelectCommand.h"
#include "components/Destroy.h"
#include "tags/LobbyTag.h"

app::cmnd::ButtonLobbySelectCommand::ButtonLobbySelectCommand(
	  app::net::Lobby const lobby
	, bool isHost
	, app::sce::SceneType & sceneControl
)
	: BaseMultiplayerCommand()
	, m_lobby(lobby)
	, m_isHost(isHost)
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
		lobbyTag.isHost = m_isHost;
		for (std::int32_t i = 0; i < lobbyTag.players.size(); ++i)
		{
			if (i >= m_lobby.getPlayers().size()) { break; }

			auto & player = lobbyTag.players.at(i);
			auto const & playerName = this->getPlayerName(i);
			player = playerName;
		}
		constexpr auto PACKET_TYPE = app::net::PacketType::LOBBY_JOINED;
		if (!m_client.send(PACKET_TYPE))
		{
			this->output("Failed to send packet");
		}
		if (!m_client.send(m_lobby.getId()))
		{
			this->output({ "Failed to send lobby id[", std::to_string(m_lobby.getId()), "]" });
		}
		const auto USER_NAME = std::string("Bob"); // hard coded constant, to be removed when textbox is made
		if (!m_client.send(USER_NAME))
		{
			this->output({ "Failed to send player name '", USER_NAME, "'" });
		}
		if (!m_client.get(lobbyTag.playerIndex))
		{
			this->output({ "Failed to retrieve player index" });
		}
		m_registry.accommodate<tag::Lobby>(m_registry.create(), std::move(lobbyTag));
	}
}

app::net::Lobby::Player const & app::cmnd::ButtonLobbySelectCommand::getPlayerName(std::int32_t const & index) const
{
	auto itt = m_lobby.getPlayers().cbegin();
	for (std::size_t i = 0; i < index; ++i) { ++itt; }
	return *itt;
}
