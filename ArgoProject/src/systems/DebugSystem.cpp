#include "stdafx.h"
#include "DebugSystem.h"
#include "singletons/KeyHandlerSingleton.h"
#include "singletons/ClientSingleton.h"

app::sys::DebugSystem::DebugSystem(app::sce::SceneType& _targetScene)
	: m_keyHandler(app::sin::KeyHandler::get())
	, m_client(app::sin::Client::get())
	, m_connected(false)
	, m_targetScene(_targetScene)
{
}

void app::sys::DebugSystem::update(app::time::seconds const & dt)
{
	if constexpr (s_DEBUG_MODE)
	{
		serverTesting();
	}
}

void app::sys::DebugSystem::serverTesting()
{
//this stuff will happen when the multiplayer button is pressed.
	if (m_keyHandler.isKeyPressed(SDLK_p) && !m_connected)
	{
		m_connected = true;

		app::Console::writeLine("CONNECTING TO SERVER");
		if (SDLNet_Init() != NULL)
		{
			app::Console::writeLine({ "Failed to initialise SDL_net: ", SDLNet_GetError() });
		}


		if (!m_client.initNetwork("localhost", 27000))
		{
			m_connected = false;
			app::Console::writeLine("Could not connect to server, make sure server is running");
		}
		m_updateVariable = true;
	}
	if (m_updateVariable && m_connected)
	{
		m_updateVariable = false;

		app::Console::writeLine("sending name to server");
		std::string name = "Bob";
		//define the type of packet we are about to send
		app::net::Packet packetType = app::net::Packet::CLIENT_NAME;
		//send the packet out
		m_client.send(name, packetType);
		m_targetScene = app::sce::SceneType::LobbySelect;
	}
	if (m_connected)
	{
		app::net::Packet packetType;
		//get the player name here and send the name to the server.
		if (m_client.checkSocket()) {
			if (!m_client.get(packetType))
			{
				app::Console::writeLine("issue receiving the packet");
			}
			if (!m_client.send(packetType))
			{
				app::Console::writeLine("issue sending the packet");
			}
		}
	}
	if (m_keyHandler.isKeyPressed(SDLK_l))
	{
		//simulate logic for when create new lobby is clicked
		std::string name = "Bob";
		app::net::Packet packetType = app::net::Packet::LOBBY_CREATE;
		m_client.send(name, packetType);
	}
}
