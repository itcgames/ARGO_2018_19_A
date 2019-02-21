#include "stdafx.h"
#include "ButtonMainMenuMultiplayerConnectCommand.h"
#include "factories/entities/modals/AskNameFactory.h"

app::cmnd::ButtonMainMenuMultiplayerConnectCommand::ButtonMainMenuMultiplayerConnectCommand(std::string && serverIp, std::int32_t serverPort, app::Entity callingEntity, app::sce::SceneType & sceneManagerControl)
	: BaseMultiplayerCommand()
	, m_serverIp(serverIp)
	, m_serverPort(serverPort)
	, m_sceneManagerControl(sceneManagerControl)
	, m_callingEntity(callingEntity)
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
			app::fact::mod::AskNameFactory(m_callingEntity, m_sceneManagerControl).create();
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
			app::fact::mod::AskNameFactory(m_callingEntity, m_sceneManagerControl).create();
		}
		else
		{

		}
	}
}
