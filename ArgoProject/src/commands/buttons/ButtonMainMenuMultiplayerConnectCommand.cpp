#include "stdafx.h"
#include "ButtonMainMenuMultiplayerConnectCommand.h"

app::cmnd::ButtonMainMenuMultiplayerConnectCommand::ButtonMainMenuMultiplayerConnectCommand(
	  std::string && serverIp
	, std::int32_t serverPort
	, app::Entity const callingEntity
	, app::sce::SceneType & sceneManagerControl
)
	: BaseMultiplayerCommand()
	, m_serverIp(serverIp)
	, m_serverPort(serverPort)
	, m_askNameFactory(callingEntity, sceneManagerControl)
{
}

void app::cmnd::ButtonMainMenuMultiplayerConnectCommand::execute()
{
	if (m_client.hasInit()) { return; }
	if constexpr (s_DEBUG_MODE)
	{
		if (m_client.initNetwork(m_serverIp, m_serverPort))
		{
			app::Console::write({ "Connection to server[", m_serverIp, "]:[", std::to_string(m_serverPort), "]" });
			app::Console::writeLine(" successfull !");
			for (auto const & entity : m_askNameFactory.create())
			{
				Console::writeLine({ "  Created entity[", std::to_string(entity), "]" });
			}
		}
		else
		{
			app::Console::write({ "Connection to server[", m_serverIp, "]:[", std::to_string(m_serverPort), "]" });
			app::Console::writeLine(" failed !");
		}
	}
	else
	{
		if (m_client.initNetwork(m_serverIp, m_serverPort))
		{
			auto entities = m_askNameFactory.create();
			entities.clear();
		}
		else
		{

		}
	}
}
