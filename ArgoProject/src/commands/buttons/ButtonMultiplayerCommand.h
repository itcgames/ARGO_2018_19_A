#ifndef _BUTTON_MULTIPLAYER_COMMAND_H
#define _BUTTON_MULTIPLAYER_COMMAND_H

#include "../BaseCommand.h"
#include "network/Client.h"

namespace app::cmnd
{
	class ButtonMultiplayerCommand : public BaseCommand
	{
	public: // Constructors/Destructor/Assignments
		ButtonMultiplayerCommand();
		virtual ~ButtonMultiplayerCommand() = default;

		ButtonMultiplayerCommand(ButtonMultiplayerCommand const &) = default;
		ButtonMultiplayerCommand & operator=(ButtonMultiplayerCommand const &) = default;

		ButtonMultiplayerCommand(ButtonMultiplayerCommand &&) = default;
		ButtonMultiplayerCommand & operator=(ButtonMultiplayerCommand &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
		app::net::Client & m_client;
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_BUTTON_MULTIPLAYER_COMMAND_H
