#include "stdafx.h"
#include "DestroySystem.h"
#include "components/Destroy.h"

void app::sys::DestroySystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Destroy>()
		.each([&, this](app::Entity const entity, comp::Destroy & destroy)
	{
		destroy.timer += dt.count();
		if (destroy.timer > destroy.timeToLive)
		{
			m_registry.destroy(entity);
		}
	});
}
