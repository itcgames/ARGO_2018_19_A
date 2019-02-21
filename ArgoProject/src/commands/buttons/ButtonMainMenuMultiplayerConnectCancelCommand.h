#ifndef _BUTTON_MAINMENU_MULTIPLAYER_CONNECT_CANCEL_COMMAND_H
#define _BUTTON_MAINMENU_MULTIPLAYER_CONNECT_CANCEL_COMMAND_H

#include "BaseMultiplayerCommand.h"

namespace app::cmnd
{
	class ButtonMainMenuMultiplayerConnectCancelCommand : public BaseMultiplayerCommand
	{
	public: // Constructors/Destructor/Assignments
		ButtonMainMenuMultiplayerConnectCancelCommand(app::Entity const & callingEntity);
		virtual ~ButtonMainMenuMultiplayerConnectCancelCommand() = default;

		ButtonMainMenuMultiplayerConnectCancelCommand(ButtonMainMenuMultiplayerConnectCancelCommand const &) = default;
		ButtonMainMenuMultiplayerConnectCancelCommand & operator=(ButtonMainMenuMultiplayerConnectCancelCommand const &) = default;

		ButtonMainMenuMultiplayerConnectCancelCommand(ButtonMainMenuMultiplayerConnectCancelCommand &&) = default;
		ButtonMainMenuMultiplayerConnectCancelCommand & operator=(ButtonMainMenuMultiplayerConnectCancelCommand &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		void setEntites(std::vector<app::Entity> const & entities);
		virtual void execute() final override;
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
		std::vector<app::Entity> m_entities;
		app::Entity const m_callingEntity;
	};
}

#endif // !_BUTTON_MAINMENU_MULTIPLAYER_CONNECT_CANCEL_COMMAND_H
