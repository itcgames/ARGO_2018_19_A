#include "stdafx.h"
#include "ButtonMainMenuMultiplayerConnectConfirmCommand.h"

app::cmnd::ButtonMainMenuMultiplayerConnectConfirmCommand::ButtonMainMenuMultiplayerConnectConfirmCommand(
	  app::Entity const callingEntity
	, std::string const & userName
	, app::sce::SceneType & sceneManagerControl
)
	: BaseMultiplayerCommand()
	, m_callingEntity(callingEntity)
	, m_userName(userName)
	, m_sceneManagerControl(sceneManagerControl)
{
}

void app::cmnd::ButtonMainMenuMultiplayerConnectConfirmCommand::execute()
{
	constexpr auto PACKET_TYPE = app::net::PacketType::CLIENT_NAME;
	if (m_client.send(m_userName, PACKET_TYPE))
	{
		// Sending successfull
		this->output({ "Sending username[", m_userName, "] successfull !" });
		m_sceneManagerControl = app::sce::SceneType::LobbySelect;
	}
	else
	{
		// Sending failed
		this->output({ "Sending username[", m_userName, "] failed !" });
	}
}
