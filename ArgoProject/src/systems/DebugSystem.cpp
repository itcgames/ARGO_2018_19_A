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
		this->sceneSwapping();
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

void app::sys::DebugSystem::sceneSwapping()
{
	using Scene = app::sce::SceneType;
	if (m_keyHandler.isKeyPressed(SDLK_1)) { m_targetScene = Scene::Splash; }
	if (m_keyHandler.isKeyPressed(SDLK_2)) { m_targetScene = Scene::MainMenu; }
	if (m_keyHandler.isKeyPressed(SDLK_3)) { m_targetScene = Scene::Credits; }
	if (m_keyHandler.isKeyPressed(SDLK_4)) { m_targetScene = Scene::CharacterSelect; }
	if (m_keyHandler.isKeyPressed(SDLK_5)) { m_targetScene = Scene::TutorialLevel; }
	if (m_keyHandler.isKeyPressed(SDLK_6)) { m_targetScene = Scene::LevelSelect; }
	if (m_keyHandler.isKeyPressed(SDLK_7)) { m_targetScene = Scene::Level; }
	if (m_keyHandler.isKeyPressed(SDLK_8)) { m_targetScene = Scene::LobbySelect; }
	if (m_keyHandler.isKeyPressed(SDLK_9)) { m_targetScene = Scene::Lobby; }
	if (m_keyHandler.isKeyPressed(SDLK_0)) { m_targetScene = Scene::MultiplayerLevel; }
}
