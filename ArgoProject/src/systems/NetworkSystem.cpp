#include "stdafx.h"
#include "NetworkSystem.h"
#include "singletons/ClientSingleton.h"
#include "commands/buttons/ButtonLobbySelectRefreshCommand.h"
#include "commands/buttons/ButtonLobbySelectCommand.h"

#include "components/Widget.h"
#include "tags/LobbyTag.h"

app::sys::NetworkSystem::NetworkSystem(app::sce::SceneType & sceneControl)
	: BaseSystem()
	, m_client(app::sin::Client::get())
	, m_packetType()
	, m_sceneControl(sceneControl)
{
}

void app::sys::NetworkSystem::update(app::time::seconds const & dt)
{
	if (m_client.hasInit() && m_client.checkSocket())
	{
		m_packetType = app::net::PacketType::UNKNOWN;
		if (!m_client.get(m_packetType))
		{
			this->output("Failed to retrieve packet type");
		}
		if (m_client.processPacket(m_packetType))
		{
			this->output("Processed packet successfully");
			if (m_packetType == app::net::PacketType::LOBBY_WAS_CREATED)
			{
				this->output("Lobby was created");
				auto buttonView = m_registry.view<comp::Widget>();
				auto entities = std::forward_list<app::Entity>();
				for (auto const & entity : buttonView) { entities.push_front(entity); }
				std::make_unique<cmnd::ButtonLobbySelectRefreshCommand>(entities, m_sceneControl)->execute();
				auto const & lobby = m_client.getLobbies().back();
				std::make_unique<cmnd::ButtonLobbySelectCommand>(lobby, m_sceneControl)->execute();
			}
		}
		else
		{
			this->output("Failed to process packet");
		}
	}
}

void app::sys::NetworkSystem::output(std::string const & msg) const
{
	if constexpr (s_DEBUG_MODE)
	{
		app::Console::writeLine(msg);
	}
}

void app::sys::NetworkSystem::output(std::initializer_list<std::string> const & msgs) const
{
	if constexpr (s_DEBUG_MODE)
	{
		app::Console::writeLine(msgs);
	}
}
