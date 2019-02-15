#ifndef _COMPONENTS_NODE_H
#define _COMPONENTS_NODE_H

#include "commands/BaseCommand.h"

namespace app::comp
{
	struct Node
	{
	public: // Constructors/Destructor/Assignments
		Node() = default;
		~Node() = default;

		Node(Node const &) = default;
		Node & operator=(Node const &) = default;

		Node(Node &&) = default;
		Node & operator=(Node &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		std::list<std::shared_ptr<app::cmnd::BaseCommand>> m_loopCommands;
		std::list<std::shared_ptr<app::cmnd::BaseCommand>> m_initialCommands;
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

#endif // !_COMPONENTS_NODE_H
