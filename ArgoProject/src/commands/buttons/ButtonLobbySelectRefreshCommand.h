#ifndef _BUTTON_LOBBY_SELECT_REFRESH_COMMAND_H
#define _BUTTON_LOBBY_SELECT_REFRESH_COMMAND_H

#include "BaseMultiplayerCommand.h"

namespace app::cmnd
{
	class ButtonLobbySelectRefreshCommand : public BaseMultiplayerCommand
	{
	public: // Constructors/Destructor/Assignments
		ButtonLobbySelectRefreshCommand() = default;
		virtual ~ButtonLobbySelectRefreshCommand() = default;

		ButtonLobbySelectRefreshCommand(ButtonLobbySelectRefreshCommand const &) = default;
		ButtonLobbySelectRefreshCommand & operator=(ButtonLobbySelectRefreshCommand const &) = default;

		ButtonLobbySelectRefreshCommand(ButtonLobbySelectRefreshCommand &&) = default;
		ButtonLobbySelectRefreshCommand & operator=(ButtonLobbySelectRefreshCommand &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
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
	};
}

#endif // !_BUTTON_LOBBY_SELECT_REFRESH_COMMAND_H
