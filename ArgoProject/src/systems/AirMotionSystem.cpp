#include "stdafx.h"
#include "AirMotionSystem.h"

// components
#include "components/Location.h"
#include "components/AirMotion.h"
#include "components/CharacterType.h"
#include "factories/SwordLegsFallAttackFactory.h"

void app::sys::AirMotionSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Location, comp::AirMotion>()
		.each([&, this](app::Entity const entity, comp::Location & location, comp::AirMotion & motion )
	{
		auto const & velocity = (math::toVector(motion.direction) * motion.speed) + motion.gravity;
 		auto velActual = velocity;
		if (velActual.magnitude() > comp::AirMotion::DEFAULT_MAX_SPEED)
		{
			velActual = velActual.unit() * comp::AirMotion::DEFAULT_MAX_SPEED;
		}
		if (velActual.y > 0)
		{
			auto characterTypeView = m_registry.view<comp::CharacterType>();
			if (characterTypeView.contains(entity))
			{
				auto charType = m_registry.get<comp::CharacterType>(entity);
				if (charType.type == app::comp::CharacterType::Type::SWORD_LEGS)
				{
					auto fallAttackFactory = app::fact::SwordLegsFallAttackFactory(entity);
					fallAttackFactory.create();
				}
			}
		}
		motion.speed = velActual.magnitude();
		motion.direction = velActual.toAngle();
		location.position += velActual * dt.count();
		location.orientation += motion.angularSpeed * dt.count();

	});
}
