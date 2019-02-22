#ifndef _COMPONENT_AI_H
#define _COMPONENT_AI_H

#include "commands/BaseCommand.h"

namespace app::comp
{
	struct AI
	{
	public: // Constructors/Destructor/Assignments
		AI() = default;
		~AI() = default;

		AI(AI const &) = default;
		AI & operator=(AI const &) = default;

		AI(AI &&) noexcept = default;
		AI & operator=(AI &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		std::optional<app::Entity> currentNode;
		std::list<std::shared_ptr<app::cmnd::BaseCommand>> initialCommands;
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

#endif // !_COMPONENT_AI_H
