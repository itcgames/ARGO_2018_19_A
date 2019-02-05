#ifndef _COMP_COMMANDABLE_H
#define _COMP_COMMANDABLE_H

#include "commands/BaseCommand.h"

namespace app::comp
{
	struct Commandable
	{
	public: // Constructors/Destructor/Assignments
		Commandable() = default;
		~Commandable() = default;

		Commandable(Commandable const &) = default;
		Commandable & operator=(Commandable const &) = default;

		Commandable(Commandable &&) = default;
		Commandable & operator=(Commandable &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		std::forward_list<std::shared_ptr<app::cmnd::BaseCommand>> list;
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

#endif // !_COMP_COMMANDABLE_H
