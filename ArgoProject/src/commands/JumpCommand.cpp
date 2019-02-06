#include "stdafx.h"
#include "JumpCommand.h"
#include "components/Motion.h"
#include "components/AirMotion.h"

app::cmnd::JumpCommand::JumpCommand(app::Entity const _entity, float _force)
	: m_entity(_entity)
	, m_force(_force)
{
}

void app::cmnd::JumpCommand::execute()
{
	if (m_registry.has<comp::AirMotion>(m_entity))
	{
		//handle double jump later
		auto & airMotion = m_registry.get<comp::AirMotion>(m_entity);
		if (airMotion.canDoubleJump)
		{
			auto impulse = math::Vector2f(0.0f, -1.0f) * m_force;
			auto const & velocity = (math::toVector(airMotion.direction) * airMotion.speed) + impulse;
			airMotion.direction = velocity.toAngle();
			airMotion.speed = velocity.magnitude();
			airMotion.canDoubleJump = false;
		}
	}
	else
	{
		auto & motion = m_registry.get<comp::Motion>(m_entity);
		auto impulse = math::Vector2f(0.0f, -1.0f) * m_force;
		auto const & velocity = (math::toVector(motion.direction) * motion.speed) + impulse;
		motion.direction = velocity.toAngle();
		motion.speed = velocity.magnitude();

		auto airMotion = comp::AirMotion();
		airMotion.speed = motion.speed;
		airMotion.direction = motion.direction;
		airMotion.angularSpeed = motion.angularSpeed;
		airMotion.maxSpeed = 500.0f;
		m_registry.assign<comp::AirMotion>(m_entity, std::move(airMotion));
		m_registry.remove<comp::Motion>(m_entity);
	}
	
}
