#include "stdafx.h"
#include "MotionSystem.h"

// components
#include "components/Location.h"
#include "components/Motion.h"

void app::sys::MotionSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Location, comp::Motion>()
		.each([&, this](app::Entity const entity, comp::Location & location, comp::Motion & motion)
	{
		auto const & velocity = math::toVector(motion.direction) * motion.speed;
		location.position += velocity * dt.count();
		location.orientation += motion.angularSpeed * dt.count();
	});
}
