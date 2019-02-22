#ifndef _TEST_COMMAND_H
#define _TEST_COMMAND_H

#include "BaseCommand.h"

namespace app::cmnd
{
	class TestCommand : public BaseCommand
	{
	public: // Constructors/Destructor/Assignments
		TestCommand() = default;
		virtual ~TestCommand() = default;

		TestCommand(TestCommand const &) = default;
		TestCommand & operator=(TestCommand const &) = default;

		TestCommand(TestCommand &&) = default;
		TestCommand & operator=(TestCommand &&) = default;

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

#endif // !_TEST_COMMAND_H
