#include "stdafx.h"
#include "LoadingSystem.h"

// components
#include "components/Animator.h"
#include "components/Render.h"

void app::sys::LoadingSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Animator, comp::Render>()
		.each([&, this](app::Entity const entity, comp::Animator & animator, comp::Render & render)
	{
		//if(render.texture == m_resourceManager.getTexture(m_textureKey))
	});
}
