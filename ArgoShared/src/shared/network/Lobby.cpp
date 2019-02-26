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
std::optional<std::size_t> app::net::Lobby::addPlayer(std::int32_t const & id, const std::string& name)
{
	for (std::size_t i = 0; i < m_players.size(); ++i)
	{
		if (m_players.at(i).has_value()) { continue; }
		m_players.at(i).emplace(std::make_pair(id, name));
		return i;
	}
	return std::nullopt;
}
