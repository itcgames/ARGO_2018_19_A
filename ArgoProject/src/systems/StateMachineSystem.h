#ifndef _STATE_MACHINE_SYSTEM_H
#define _STATE_MACHINE_SYSTEM_H

#include "BaseSystem.h"

namespace app::sys
{
	class StateMachineSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		StateMachineSystem() = default;
		virtual ~StateMachineSystem() = default;

		StateMachineSystem(StateMachineSystem const &) = default;
		StateMachineSystem & operator=(StateMachineSystem const &) = default;

		StateMachineSystem(StateMachineSystem &&) = default;
		StateMachineSystem & operator=(StateMachineSystem &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual void update(app::time::seconds const & dt) override;
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

#endif // !_STATE_MACHINE_SYSTEM_H
