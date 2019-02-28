#ifndef _BUTTON_MAIN_MENU_EXIT_COMMAND_H
#define _BUTTON_MAIN_MENU_EXIT_COMMAND_H

#include "../BaseCommand.h"
#include "scenes/SceneType.h"

namespace app::cmnd
{
	class ButtonMainMenuExitCommand : public BaseCommand
	{
	public: // Constructors/Destructor/Assignments
		ButtonMainMenuExitCommand(app::sce::SceneType & sceneControl);
		virtual ~ButtonMainMenuExitCommand() = default;

		ButtonMainMenuExitCommand(ButtonMainMenuExitCommand const &) = default;
		ButtonMainMenuExitCommand & operator=(ButtonMainMenuExitCommand const &) = default;

		ButtonMainMenuExitCommand(ButtonMainMenuExitCommand &&) = default;
		ButtonMainMenuExitCommand & operator=(ButtonMainMenuExitCommand &&) = default;

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
		app::sce::SceneType & m_sceneControl;
	};
}

#endif // !_BUTTON_MAIN_MENU_EXIT_COMMAND_H
