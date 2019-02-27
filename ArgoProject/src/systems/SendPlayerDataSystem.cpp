#include "stdafx.h"
#include "SendPlayerDataSystem.h"

#include "singletons/ClientSingleton.h"

#include "components/Input.h"
#include "components/Location.h"
#include "tags/LobbyTag.h"

app::sys::SendPlayerDataSystem::SendPlayerDataSystem()
	: BaseSystem()
	, m_client(app::sin::Client::get())
{

}

void app::sys::SendPlayerDataSystem::update(app::time::seconds const & dt)
{
	auto const & lobbyTag = m_registry.get<tag::Lobby>();
	m_registry.view<comp::Input, comp::Location>()
		.each([&, this](app::Entity const entity, comp::Input & input, comp::Location & location)
	{
		m_client.send(app::net::PacketType::LEVEL_NEW_PLAYER_INFO);
		m_client.send(lobbyTag.id);
		auto const & playerId = lobbyTag.players[lobbyTag.playerIndex]->first;
		m_client.send(playerId);
		m_client.send(location.position);
	});
}
