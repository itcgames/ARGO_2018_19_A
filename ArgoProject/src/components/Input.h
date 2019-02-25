#ifndef _INPUT_H
#define _INPUT_H

#include "commands/BaseCommand.h"

namespace app::comp
{
	struct Input
	{
	public: // Constructors/Destructor/Assignments
		Input() = default;
		~Input() = default;

		Input(Input const &) = default;
		Input(Input &&) noexcept = default;

		Input & operator=(Input const &) = default;
		Input & operator=(Input &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		std::map<app::inp::KeyCode, std::shared_ptr<app::cmnd::BaseCommand>> keyDownCommands;
		std::map<app::inp::KeyCode, std::shared_ptr<app::cmnd::BaseCommand>> keyPressedCommands;
		bool isRight = true;
		bool canAttack = true;
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

#endif // !_INPUT_H
