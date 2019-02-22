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
		auto const & zero = decltype(animator.currentFrame)::zero;
		while (animator.perFrame * calculateStep(animator.currentFrame) < animator.time)
		{
			if (animator.currentFrame.x < (animator.numOfFrames.x - 1)) { ++animator.currentFrame.x; }
			else if (animator.currentFrame.y < (animator.numOfFrames.y - 1)) { animator.currentFrame.x = zero; ++animator.currentFrame.y; }
			else if (animator.loop) { animator.currentFrame = zero; animator.time = 0.0f; }
			else { animator.time = 0.0f; }
		}
		m_rect.x = animator.position.x + static_cast<std::int32_t>(animator.frameSize.x * animator.currentFrame.x);
		m_rect.y = animator.position.y + static_cast<std::int32_t>(animator.frameSize.y * animator.currentFrame.y);
		m_rect.w = static_cast<std::int32_t>(animator.frameSize.x);
		m_rect.h = static_cast<std::int32_t>(animator.frameSize.y);
		render.source = m_rect;
	});
}

constexpr int app::sys::AnimatorSystem::calculateStep(math::Vector2i const & frameStep)
{
	return (frameStep.x + 1) * (frameStep.y + 1);
}
