#ifndef _BASE_MULTIPLAYER_COMMAND_H
#define _BASE_MULTIPLAYER_COMMAND_H

#include "../BaseCommand.h"
#include "network/Client.h"

namespace app::cmnd
{
	class BaseMultiplayerCommand : public BaseCommand
	{
	public: // Constructors/Destructor/Assignments
		BaseMultiplayerCommand();
		virtual ~BaseMultiplayerCommand() = default;

		BaseMultiplayerCommand(BaseMultiplayerCommand const &) = default;
		BaseMultiplayerCommand & operator=(BaseMultiplayerCommand const &) = default;

		BaseMultiplayerCommand(BaseMultiplayerCommand &&) = default;
		BaseMultiplayerCommand & operator=(BaseMultiplayerCommand &&) = default;

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

#endif // !_BASE_MULTIPLAYER_COMMAND_H
