#include "stdafx.h"
#include "Lobby.h"

/// <summary>
/// Sets the name of the lobby
/// </summary>
/// <param name="name"></param>
void app::net::Lobby::setName(const std::string& name)
{
	m_lobbyName = name;
}

/// <summary>
/// Getter got the name of the lobby.
/// </summary>
/// <returns>string representing name of the lobby</returns>
const std::string& app::net::Lobby::getName() const
{
	return m_lobbyName;
}

/// <summary>
/// Insert a player socket and name into player map
/// </summary>
/// <param name="socket">socket of the client</param>
/// <param name="name">name of the client</param>
void app::net::Lobby::addPlayer(int id, const std::string& name)
{
	m_players.insert(std::pair<int, std::string>(id, name));
}
