#ifndef _BUTTON_LOBBY_SELECT_COMMAND_H
#define _BUTTON_LOBBY_SELECT_COMMAND_H

#include "BaseMultiplayerCommand.h"
#include "shared/network/Lobby.h"

namespace app::cmnd
{
	class ButtonLobbySelectCommand : public BaseMultiplayerCommand
	{
	public: // Constructors/Destructor/Assignments
		ButtonLobbySelectCommand(app::net::Lobby const lobby);
		virtual ~ButtonLobbySelectCommand() = default;

		ButtonLobbySelectCommand(ButtonLobbySelectCommand const &) = default;
		ButtonLobbySelectCommand & operator=(ButtonLobbySelectCommand const &) = default;

		ButtonLobbySelectCommand(ButtonLobbySelectCommand &&) = default;
		ButtonLobbySelectCommand & operator=(ButtonLobbySelectCommand &&) = default;

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
		app::net::Lobby const m_lobby;
	};
}

#endif // !_BUTTON_LOBBY_SELECT_COMMAND_H
