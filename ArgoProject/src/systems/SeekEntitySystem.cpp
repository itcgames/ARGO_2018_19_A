#include "stdafx.h"
#include "SeekEntitySystem.h"
#include "components/SeekEntity.h"
#include "components/Location.h"
#include "components/Motion.h"
#include "components/Collision.h"
#include "components/Destroy.h"

void app::sys::SeekEntitySystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::SeekEntity, comp::Location, comp::Motion, comp::Collision>()
		.each([&, this](app::Entity const entity, comp::SeekEntity& seek, comp::Location& location, comp::Motion& motion, comp::Collision& collision)
	{
		if (m_registry.valid(seek.entity))
		{
			//get location from entity to seek
			auto followLocation = m_registry.get<comp::Location>(seek.entity);

			math::Vector2f vecBetweenPoints = followLocation.position - location.position;

			motion.direction = vecBetweenPoints.toAngle();

			collision.passable = true;

		}
		else
		{
			m_registry.destroy(entity);
		}
	});
}
