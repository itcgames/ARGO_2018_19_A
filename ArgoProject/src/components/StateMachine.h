#ifndef _COMPONENTS_STATE_MACHINE_H
#define _COMPONENTS_STATE_MACHINE_H

#include "fsm/BaseStateMachine.h"

namespace app::comp
{
	struct StateMachine
	{
	public: // Constructors/Destructor/Assignments
		StateMachine() = default;
		~StateMachine() = default;

		StateMachine(StateMachine const &) = default;
		StateMachine & operator=(StateMachine const &) = default;

		StateMachine(StateMachine &&) = default;
		StateMachine & operator=(StateMachine &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		std::unique_ptr<fsm::BaseStateMachine> instance;
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

#endif // !_COMPONENTS_STATE_MACHINE_H
