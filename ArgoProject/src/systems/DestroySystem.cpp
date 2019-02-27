#include "stdafx.h"
#include "DestroySystem.h"
#include "components/Destroy.h"
#include "components/Tiled.h"

void app::sys::DestroySystem::update(app::time::seconds const & dt)
{
	auto tilesView = m_registry.view<comp::Tiled>();
	m_registry.view<comp::Destroy>()
		.each([&, this](app::Entity const entity, comp::Destroy & destroy)
	{
		destroy.timer += dt.count();
		if (destroy.timer > destroy.timeToLive)
		{
			if (tilesView.contains(entity))
			{
				auto destroyView = m_registry.view<comp::Destroy>();
				auto const & tileComp = tilesView.get(entity);
				for (auto & e : tileComp.tiles)
				{
					if (!destroyView.contains(e)) { m_registry.assign<comp::Destroy>(e); }
				}
			}
			m_registry.destroy(entity);
		}
	});
}
