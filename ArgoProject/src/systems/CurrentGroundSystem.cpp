#include "stdafx.h"
#include "CurrentGroundSystem.h"

// components
#include "components/Location.h"
#include "components/Motion.h"
#include "components/AirMotion.h"
#include "components/PlatformDrop.h"
#include "components/Dimensions.h"
#include "components/CurrentGround.h"
#include "components/Input.h"

void app::sys::CurrentGroundSystem::update(app::time::seconds const & dt)
{
	auto inputView = m_registry.view<comp::Input>();
	auto groundView = m_registry.view<comp::Location, comp::Dimensions>();
	m_registry.view<comp::Location, comp::Dimensions, comp::Motion, comp::CurrentGround>()
		.each([&, this](app::Entity const entity, comp::Location & location, comp::Dimensions size, comp::Motion & motion, comp::CurrentGround & ground)
	{
		if (ground.currentGround.has_value() && groundView.contains(ground.currentGround.value()))
		{
			auto const &[targetPlatformPos, targetPlatformSize] = groundView.get<comp::Location, comp::Dimensions>(ground.currentGround.value());
			float rightSide = targetPlatformPos.position.x + (targetPlatformSize.size.x / 2);
			float leftSide = targetPlatformPos.position.x - (targetPlatformSize.size.x / 2);
			if (location.position.x + (size.size.x / 2) < leftSide || location.position.x - (size.size.x / 2) > rightSide)
			{
				auto airMotion = comp::AirMotion();
				airMotion.speed = motion.speed;
				airMotion.direction = motion.direction;
				airMotion.angularSpeed = motion.angularSpeed;
				m_registry.assign<comp::AirMotion>(entity, std::move(airMotion));
				m_registry.remove<comp::Motion>(entity);
				ground.currentGround.reset();
			}
		}
		else 
		{
			if (inputView.contains(entity))
			{
				auto airMotion = comp::AirMotion();
				airMotion.speed = motion.speed;
				airMotion.direction = motion.direction;
				airMotion.angularSpeed = motion.angularSpeed;
				m_registry.assign<comp::AirMotion>(entity, std::move(airMotion));
				m_registry.remove<comp::Motion>(entity);
				ground.currentGround.reset();
			}
		}
	});
}