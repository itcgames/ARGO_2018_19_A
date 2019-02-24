#include "stdafx.h"
#include "DiscReturnSystem.h"
#include "components/Disc.h"
#include "components/Motion.h"
#include "components/SeekEntity.h"

void app::sys::DiscReturnSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Disc, comp::Motion>()
		.each([&, this](app::Entity const entity, comp::Disc & disc, comp::Motion & motion)
	{
		if (motion.speed < SPEED_CUTOFF && !m_registry.has<comp::SeekEntity>(entity))
		{
			auto seek = comp::SeekEntity();
			seek.entity = disc.entity;
			m_registry.assign<decltype(seek)>(entity, std::move(seek));
			motion.drag = disc.DRAG_WHEN_SLOWED_DOWN;
			motion.speed = disc.SPEED_WHEN_SLOWED_DOWN;
			disc.backToPlayer = true;
		}
	});
}
