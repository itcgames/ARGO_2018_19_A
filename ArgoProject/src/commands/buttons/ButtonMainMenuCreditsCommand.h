#ifndef _BUTTON_MAIN_MENU_CREDITS_COMMAND_H
#define _BUTTON_MAIN_MENU_CREDITS_COMMAND_H

#include "../BaseCommand.h"
#include "scenes/SceneType.h"

namespace app::cmnd
{
	class ButtonMainMenuCreditsCommand : public BaseCommand
	{
	public: // Constructors/Destructor/Assignments
		ButtonMainMenuCreditsCommand(app::sce::SceneType & sceneControl);
		virtual ~ButtonMainMenuCreditsCommand() = default;

		ButtonMainMenuCreditsCommand(ButtonMainMenuCreditsCommand const &) = default;
		ButtonMainMenuCreditsCommand & operator=(ButtonMainMenuCreditsCommand const &) = default;

		ButtonMainMenuCreditsCommand(ButtonMainMenuCreditsCommand &&) = default;
		ButtonMainMenuCreditsCommand & operator=(ButtonMainMenuCreditsCommand &&) = default;

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

#endif // !_BUTTON_MAIN_MENU_CREDITS_COMMAND_H
