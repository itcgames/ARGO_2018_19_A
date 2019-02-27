#ifndef	_AXE_RUN_ANIMATION_STATE_H
#define _AXE_RUN_ANIMATION_STATE_H

#include "AnimationState.h"

namespace app::fsm::sta
{
	class AxeRunAnimationState : public AnimationState
	{
	public: // Constructors/Destructor/Assignments
		AxeRunAnimationState(app::Entity const entity);
		virtual ~AxeRunAnimationState() = default;

		AxeRunAnimationState(AxeRunAnimationState const &) = default;
		AxeRunAnimationState & operator=(AxeRunAnimationState const &) = default;

		AxeRunAnimationState(AxeRunAnimationState &&) = default;
		AxeRunAnimationState & operator=(AxeRunAnimationState &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
		comp::Render generateAnimationRender() const;
		comp::Animator generateAnimator() const;
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_AI_WALKING_ANIMATION_STATE_H
