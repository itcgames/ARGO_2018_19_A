#ifndef _ANIMATION_STATE_MACHINE_H
#define _ANIMATION_STATE_MACHINE_H

#include "BaseStateMachine.h"

namespace app::fsm
{
	class AnimationStateMachine : public BaseStateMachine
	{
	public: // Constructors/Destructor/Assignments
		AnimationStateMachine() = default;
		virtual ~AnimationStateMachine() = default;

		AnimationStateMachine(AnimationStateMachine const &) = default;
		AnimationStateMachine & operator=(AnimationStateMachine const &) = default;

		AnimationStateMachine(AnimationStateMachine &&) = default;
		AnimationStateMachine & operator=(AnimationStateMachine &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual void update(app::time::seconds const & dt) final override {}
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

#endif // !_ANIMATION_STATE_MACHINE_H
