#include "stdafx.h"
#include "DebugSystem.h"
#include "singletons/KeyHandlerSingleton.h"

app::sys::DebugSystem::DebugSystem()
	: m_keyHandler(app::sin::KeyHandler::get())
	, m_client()
{
}

void app::sys::DebugSystem::update(app::time::seconds const & dt)
{
	
	if (m_keyHandler.isKeyPressed(SDLK_p))
	{
		if (SDLNet_Init() != NULL)
		{
			std::cout << "Failed to intialise SDN_net: " << SDLNet_GetError() << "\n";
		}


		m_client.InitNetwork("localhost", 27000);
		updateVariable = true;

	}
	if (updateVariable)
	{
		app::Console::writeLine("asking server to update wood");
		m_client.SendData(NULL, 0, m_client.FLAG_WOOD_UPDATE);

		if (m_client.CheckSocket()) {
			uint16_t length, flag;
			uint8_t* data = m_client.RecvData(&length);

			uint16_t offset = 0;
			while (offset < length) {
				m_client.ProcessData(data, &offset);
			}

			free(data);
			updateVariable = false;
		}
	}

}
