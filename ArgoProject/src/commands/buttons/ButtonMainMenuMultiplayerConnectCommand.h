﻿#ifndef _BUTTON_MAINMENU_MULTIPLAYER_CONNECT_COMMAND_H
#define _BUTTON_MAINMENU_MULTIPLAYER_CONNECT_COMMAND_H

#include "BaseMultiplayerCommand.h"
#include "scenes/SceneType.h"
#include "factories/entities/modals/AskNameFactory.h"

namespace app::cmnd
{
	class ButtonMainMenuMultiplayerConnectCommand : public BaseMultiplayerCommand
	{
	public: // Constructors/Destructor/Assignments
		ButtonMainMenuMultiplayerConnectCommand(std::string && serverIp, std::int32_t serverPort, app::Entity const callingEntity, app::Entity const followEntity, app::sce::SceneType & sceneManagerControl);
		virtual ~ButtonMainMenuMultiplayerConnectCommand() = default;

		ButtonMainMenuMultiplayerConnectCommand(ButtonMainMenuMultiplayerConnectCommand const &) = default;
		ButtonMainMenuMultiplayerConnectCommand & operator=(ButtonMainMenuMultiplayerConnectCommand const &) = default;

		ButtonMainMenuMultiplayerConnectCommand(ButtonMainMenuMultiplayerConnectCommand &&) = default;
		ButtonMainMenuMultiplayerConnectCommand & operator=(ButtonMainMenuMultiplayerConnectCommand &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual void execute() final override;
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
		std::string const m_serverIp;
		std::int32_t const m_serverPort;
		app::fact::mod::AskNameFactory m_askNameFactory;
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_BUTTON_MAINMENU_MULTIPLAYER_CONNECT_COMMAND_H
