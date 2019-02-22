#include "stdafx.h"
#include "DropCommand.h"

#include "components/Motion.h"
#include "components/AirMotion.h"
#include "components/PlatformDrop.h"
#include "components/CurrentGround.h"
#include "components/Platform.h"

app::cmnd::DropCommand::DropCommand(app::Entity const _entity)
	:m_entity(_entity)
{
}

void app::cmnd::DropCommand::execute()
{
	if (m_registry.has<comp::Motion>(m_entity))
	{
		auto & ground = m_registry.get<comp::CurrentGround>(m_entity);
		if (m_registry.has<comp::Platform>(ground.currentGround.value()))
		{
			auto & motion = m_registry.get<comp::Motion>(m_entity);
			auto airMotion = comp::AirMotion();
			airMotion.speed = motion.speed;
			airMotion.direction = motion.direction;
			airMotion.angularSpeed = motion.angularSpeed;
			m_registry.assign<comp::AirMotion>(m_entity, std::move(airMotion));
			m_registry.remove<comp::Motion>(m_entity);
			ground.currentGround.reset();
			auto & fallCheck = m_registry.get<comp::PlatformDrop>(m_entity);
			fallCheck.falling = true;
		}
	}
}