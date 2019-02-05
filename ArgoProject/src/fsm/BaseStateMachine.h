#ifndef _FINITE_STATE_MACHINES_BASE_STATE_MACHINE_H
#define _FINITE_STATE_MACHINES_BASE_STATE_MACHINE_H

#include "BaseState.h"

namespace app::fsm
{
	class BaseStateMachine
	{
	public: // Constructors/Destructor/Assignments
		BaseStateMachine(std::shared_ptr<BaseState> state);
		virtual ~BaseStateMachine() = default;

		BaseStateMachine(BaseStateMachine const &) = default;
		BaseStateMachine & operator=(BaseStateMachine const &) = default;

		BaseStateMachine(BaseStateMachine &&) = default;
		BaseStateMachine & operator=(BaseStateMachine &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual void update(app::time::seconds const & dt) abstract;
		virtual void setState(std::shared_ptr<BaseState> newState);
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
		std::shared_ptr<BaseState> m_state;
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_FINITE_STATE_MACHINES_BASE_STATE_MACHINE_H
