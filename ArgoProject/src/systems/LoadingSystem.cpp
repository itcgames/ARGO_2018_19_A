#include "stdafx.h"
#include "LoadingSystem.h"

// components
#include "components/Animator.h"
#include "components/Render.h"
#include "components/AnimatedImage.h"

void app::sys::LoadingSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Animator, comp::Render, comp::AnimatedImage>()
		.each([&, this](app::Entity const entity, comp::Animator & animator, comp::Render & render, comp::AnimatedImage & animatedImage)
	{
		//animation complete 
		if (animator.currentFrame.x == (animator.numOfFrames.x - 1) && animator.currentFrame.y == (animator.numOfFrames.y - 1))
		{
			//render.texture = texture
		}
	});
}
