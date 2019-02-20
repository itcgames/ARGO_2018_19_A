#include "stdafx.h"
#include "ButtonMainMenuMultiplayerConnectConfirmCommand.h"

app::cmnd::ButtonMainMenuMultiplayerConnectConfirmCommand::ButtonMainMenuMultiplayerConnectConfirmCommand(
	  app::Entity callingEntity
	, std::string const & userName
	, app::sce::SceneType & sceneManagerControl
)
	: ButtonMainMenuMultiplayerCommand()
	, m_callingEntity(callingEntity)
	, m_sceneManagerControl(sceneManagerControl)
	, m_userName(userName)
{
}

void app::cmnd::ButtonMainMenuMultiplayerConnectConfirmCommand::execute()
{
	constexpr auto PACKET_TYPE = app::net::PacketType::CLIENT_NAME;
	if (m_client.send(m_userName, PACKET_TYPE))
	{
		// Sending successfull
		this->output({ "Sending username[", m_userName, "] successfull !" });
	}
	else
	{
		// Sending failed
		this->output({ "Sending username[", m_userName, "] failed !" });
	}
}
