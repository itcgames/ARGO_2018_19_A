#ifndef _AI_WALKING_ANIMATION_STATE_H
#define _AI_WALKING_ANIMATION_STATE_H

#include "AnimationState.h"

namespace app::fsm::sta
{
	class AiWalkingAnimationState : public AnimationState
	{
	public: // Constructors/Destructor/Assignments
		AiWalkingAnimationState(app::Entity const entity);
		virtual ~AiWalkingAnimationState() = default;

		AiWalkingAnimationState(AiWalkingAnimationState const &) = default;
		AiWalkingAnimationState & operator=(AiWalkingAnimationState const &) = default;

		AiWalkingAnimationState(AiWalkingAnimationState &&) = default;
		AiWalkingAnimationState & operator=(AiWalkingAnimationState &&) = default;

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
