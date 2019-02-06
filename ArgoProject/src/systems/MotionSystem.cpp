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
		auto velActual = velocity;
		if (velActual.magnitude() > motion.maxSpeed)
		{
			velActual = velActual.unit() * motion.maxSpeed;
		}
		location.position += velActual * dt.count();
		location.orientation += motion.angularSpeed * dt.count();
		if (motion.speed >= motion.dragCutoff) 
		{
			//simulate drag
			motion.speed *= motion.drag;
		}
		else
		{
			motion.speed = 0;
		}
	});
}
