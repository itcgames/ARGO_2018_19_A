#include "stdafx.h"
#include "ButtonMultiplayerConnectCommand.h"
#include "factories/entities/modals/AskNameFactory.h"

app::cmnd::ButtonMultiplayerConnectCommand::ButtonMultiplayerConnectCommand(std::string && serverIp, std::int32_t serverPort, app::sce::SceneType & sceneManagerControl)
	: ButtonMultiplayerCommand()
	, m_serverIp(serverIp)
	, m_serverPort(serverPort)
	, m_sceneManagerControl(sceneManagerControl)
{
}

void app::cmnd::ButtonMultiplayerConnectCommand::execute()
{
	if (m_client.hasInit()) { return; }
	if constexpr (s_DEBUG_MODE)
	{
		if (m_client.initNetwork(m_serverIp, m_serverPort))
		{
			app::Console::write({ "Connection to server[", m_serverIp, "]:[", std::to_string(m_serverPort), "]" });
			app::Console::writeLine(" successfull !");
			app::fact::mod::AskNameFactory().create();
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
			app::fact::mod::AskNameFactory().create();
		}
		else
		{

		}
	}
}
