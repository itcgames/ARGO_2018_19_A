#include "stdafx.h"
#include "DiscReturnSystem.h"
#include "components/Disc.h"
#include "components/Motion.h"
#include "components/SeekEntity.h"

void app::sys::DiscReturnSystem::update(app::time::seconds const & dt)
{
	auto seekEntityView = m_registry.view<comp::SeekEntity>();

	m_registry.view<comp::Disc, comp::Motion>()
		.each([&, this](app::Entity const entity, comp::Disc & disc, comp::Motion & motion)
	{
		if (motion.speed < SPEED_CUTOFF && !seekEntityView.contains(entity))
		{
			auto seek = comp::SeekEntity();
			seek.entity = disc.entity;
			m_registry.assign<decltype(seek)>(entity, std::move(seek));
			motion.drag = disc.s_DRAG_WHEN_SLOWED_DOWN;
			motion.speed = disc.s_SPEED_WHEN_SLOWED_DOWN;
			disc.backToPlayer = true;
			disc.passable = true;
		}
	});
}
