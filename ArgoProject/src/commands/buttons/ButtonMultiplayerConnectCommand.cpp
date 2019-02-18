#include "stdafx.h"
#include "ButtonMultiplayerConnectCommand.h"

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
		app::Console::write({ "Connection to server[", m_serverIp, "]:[", std::to_string(m_serverPort), "]" });
		if (m_client.initNetwork(m_serverIp, m_serverPort))
		{
			app::Console::writeLine(" successfull !");
		}
		else
		{
			app::Console::writeLine(" failed !");
		}
		m_sceneManagerControl = m_client.hasInit()
			? app::sce::SceneType::LobbySelect
			: app::sce::SceneType::MainMenu;
	}
	else
	{
		m_sceneManagerControl = m_client.initNetwork(m_serverIp, m_serverPort)
			? app::sce::SceneType::LobbySelect
			: app::sce::SceneType::MainMenu;
	}
}
