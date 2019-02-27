#ifndef _FINITE_STATE_MACHINES_ANIMATION_STATE_H
#define _FINITE_STATE_MACHINES_ANIMATION_STATE_H

#include "EntityState.h"
#include "resources/ResourceManager.h"
#include "components/Render.h"
#include "components/Animator.h"

namespace app::fsm::sta
{
	class AnimationState : public EntityState
	{
	public: // Constructors/Destructor/Assignments
		AnimationState(app::Entity const entity);
		virtual ~AnimationState() = default;

		AnimationState(AnimationState const &) = default;
		AnimationState & operator=(AnimationState const &) = default;

		AnimationState(AnimationState &&) = default;
		AnimationState & operator=(AnimationState &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		// Inherited via EntityState
		virtual void update(app::time::seconds const & dt) override;
		virtual void start() override;
		virtual void end() override;
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
		comp::Render m_render;
		comp::Animator m_animator;
		app::res::ResourceManager<true> & m_resourceManager;
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_FINITE_STATE_MACHINES_ANIMATION_STATE_H
