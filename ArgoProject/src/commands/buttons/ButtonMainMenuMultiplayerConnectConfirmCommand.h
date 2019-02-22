#ifndef _BUTTON_MAINMENU_MULTIPLAYER_CONNECT_CONFIRM_COMMAND_H
#define _BUTTON_MAINMENU_MULTIPLAYER_CONNECT_CONFIRM_COMMAND_H

#include "BaseMultiplayerCommand.h"
#include "scenes/SceneType.h"

namespace app::cmnd
{
	class ButtonMainMenuMultiplayerConnectConfirmCommand : public BaseMultiplayerCommand
	{
	public: // Constructors/Destructor/Assignments
		ButtonMainMenuMultiplayerConnectConfirmCommand(app::Entity const callingEntity, std::string const & userName, app::sce::SceneType & sceneManagerControl);
		virtual ~ButtonMainMenuMultiplayerConnectConfirmCommand() = default;

		ButtonMainMenuMultiplayerConnectConfirmCommand(ButtonMainMenuMultiplayerConnectConfirmCommand const &) = default;
		ButtonMainMenuMultiplayerConnectConfirmCommand & operator=(ButtonMainMenuMultiplayerConnectConfirmCommand const &) = default;

		ButtonMainMenuMultiplayerConnectConfirmCommand(ButtonMainMenuMultiplayerConnectConfirmCommand &&) = default;
		ButtonMainMenuMultiplayerConnectConfirmCommand & operator=(ButtonMainMenuMultiplayerConnectConfirmCommand &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual void execute() final override;
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
		app::Entity const m_callingEntity;
		std::string const m_userName;
		app::sce::SceneType & m_sceneManagerControl;
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_BUTTON_MAINMENU_MULTIPLAYER_CONNECT_CONFIRM_COMMAND_H
