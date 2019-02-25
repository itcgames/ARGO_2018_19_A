#include "stdafx.h"
#include "AiWalkingAnimationState.h"

app::fsm::sta::AiWalkingAnimationState::AiWalkingAnimationState(app::Entity const entity)
	: AnimationState(entity)
{
	m_render = std::move(this->generateAnimationRender());
	m_animator = std::move(this->generateAnimator());
}

app::comp::Render app::fsm::sta::AiWalkingAnimationState::generateAnimationRender() const
{
	auto render = comp::Render();

	render.texture = m_resourceManager.getTexture(app::res::TextureKey::AxeRun);
	render.border = math::Vector2f{ 30.0f, 4.0f };
	render.offset = math::Vector2f{ 15.0f, 2.0f };

	return std::move(render);
}

app::comp::Animator app::fsm::sta::AiWalkingAnimationState::generateAnimator() const
{
	auto animator = comp::Animator();

	animator.loop = true; // tell animator to loop animation when it reaches the end.
	animator.time = 0.0f; // Separate time tracking for the animation, leave it at zero
	animator.currentFrame = math::Vector2i{ 0, 0 }; // Starting frame
	animator.position = { 0, 0 }; // Starting position
	animator.frameSize = math::Vector2i{ 500, 500 }; // width,height of each frame
	animator.numOfFrames = math::Vector2i{ 7, 12 }; // number of frames in the X axis and Y axis
	animator.maxFrames = 82;
	// time it takes to switch from one frame to another.
	// calculating it by taking full_duration / (number of total frames)
	// while dealing with edge case of any of the frames being zero
	animator.perFrame = 0.02f;

	return std::move(animator);
}
