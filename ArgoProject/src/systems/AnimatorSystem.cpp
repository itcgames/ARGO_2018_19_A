#include "stdafx.h"
#include "AnimatorSystem.h"

// components
#include "components/Animator.h"
#include "components/Render.h"

void app::sys::AnimatorSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Render, comp::Animator>()
		.each([&dt, this](app::Entity const entity, comp::Render & render, comp::Animator & animator)
	{
		animator.time += dt.count();
		while (animator.perFrame * static_cast<decltype(animator.perFrame)>(animator.currentFrame + 1u) < animator.time) { ++animator.currentFrame; }
		if (animator.currentFrame >= animator.frames.size()) { animator.currentFrame = 0u; animator.time = 0.0f; }
		render.source = animator.frames.at(animator.currentFrame);
	});
}
