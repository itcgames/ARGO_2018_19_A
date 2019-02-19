#ifndef _BUTTON_MULTIPLAYER_CANCEL_COMMAND_H
#define _BUTTON_MULTIPLAYER_CANCEL_COMMAND_H

#include "ButtonMultiplayerCommand.h"

namespace app::cmnd
{
	class ButtonMultiplayerCancelCommand : public ButtonMultiplayerCommand
	{
	public: // Constructors/Destructor/Assignments
		ButtonMultiplayerCancelCommand() = default;
		ButtonMultiplayerCancelCommand(std::vector<app::Entity> const & entities);
		virtual ~ButtonMultiplayerCancelCommand() = default;

		ButtonMultiplayerCancelCommand(ButtonMultiplayerCancelCommand const &) = default;
		ButtonMultiplayerCancelCommand & operator=(ButtonMultiplayerCancelCommand const &) = default;

		ButtonMultiplayerCancelCommand(ButtonMultiplayerCancelCommand &&) = default;
		ButtonMultiplayerCancelCommand & operator=(ButtonMultiplayerCancelCommand &&) = default;

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
		void output(std::string const & message) const;
	private: // Private Static Variables
	private: // Private Member Variables
		std::vector<app::Entity> m_entities;
	};
}

#endif // !_BUTTON_MULTIPLAYER_CANCEL_COMMAND_H
