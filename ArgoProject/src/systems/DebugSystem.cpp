#include "stdafx.h"
#include "DebugSystem.h"
#include "singletons/KeyHandlerSingleton.h"

app::sys::DebugSystem::DebugSystem()
	: m_keyHandler(app::sin::KeyHandler::get())
	, m_client()
	, connected(false)
{
}

void app::sys::DebugSystem::update(app::time::seconds const & dt)
{
	////////////////////////////////////////////////////////////////////////////
	/////				* SERVER DEBUG CODE *
	////////////////////////////////////////////////////////////////////////////
	//this stuff will happen when the multiplayer button is pressed.
	if (m_keyHandler.isKeyPressed(SDLK_p) && !connected)
	{
		connected = true;

		app::Console::writeLine("CONNECTION");
		if (SDLNet_Init() != NULL)
		{
			std::cout << "Failed to intialise SDN_net: " << SDLNet_GetError() << "\n";
		}


		if (!m_client.InitNetwork("localhost", 27000))
		{
			connected = false;
			app::Console::writeLine("Could not connect to server, make sure server is running");
		}
		updateVariable = true;
	}
	if (updateVariable && connected)
	{
		updateVariable = false;

		app::Console::writeLine("asking server to update wood");
		//m_client.SendData(NULL, 0, m_client.FLAG_WOOD_UPDATE);
		std::string name = "Bob";
		auto packetType = app::net::P_CLIENT_NAME;
		//m_client.sendPacketType(packetType);
		m_client.sendString(name);

		
	}
	if (connected)
	{
		app::net::Packet packetType;
		//get the player name here and send the name to the server.
		if (m_client.CheckSocket()) {
			if (!m_client.getPacketType(packetType))
			{
				app::Console::writeLine("issue receiving the packet");
			}
			if (!m_client.sendPacketType(packetType))
			{
				app::Console::writeLine("issue sending the packet");
			}
		}
	}
	////////////////////////////////////////////////////////////////////////////
	/////				* SERVER DEBUG CODE END*
	////////////////////////////////////////////////////////////////////////////
}
