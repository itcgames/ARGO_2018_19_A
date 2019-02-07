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
 		auto velActual = velocity;
		if (velActual.magnitude() > motion.maxSpeed)
		{
			velActual = velActual.unit() * motion.maxSpeed;
		}
		motion.speed = velActual.magnitude();
		motion.direction = velActual.toAngle();
		location.position += velActual * dt.count();
		location.orientation += motion.angularSpeed * dt.count();

	});
}
