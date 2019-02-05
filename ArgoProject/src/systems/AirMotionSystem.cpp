#include "stdafx.h"
#include "AirMotionSystem.h"

// components
#include "components/Location.h"
#include "components/AirMotion.h"


void app::sys::AirMotionSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Location, comp::AirMotion>()
		.each([&, this](app::Entity const entity, comp::Location & location, comp::AirMotion & motion )
	{
		auto const & velocity = (math::toVector(motion.direction) * motion.speed) + motion.gravity;
		motion.speed = velocity.magnitude();
		motion.direction = velocity.toAngle();
		location.position += velocity * dt.count();
		location.orientation += motion.angularSpeed * dt.count();
	});
}
