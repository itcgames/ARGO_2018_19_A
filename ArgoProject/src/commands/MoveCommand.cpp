#include "stdafx.h"
#include "MoveCommand.h"
#include "components/AirMotion.h"

app::cmnd::MoveCommand::MoveCommand(app::Entity const _entity, float _dir, float _speed)
	: m_entity(_entity)
	, m_direction(_dir)
	, m_speed(_speed)
{
}

void app::cmnd::MoveCommand::execute()
{
	if (m_registry.has<comp::Motion>(m_entity))
	{
		auto & motion = m_registry.get<comp::Motion>(m_entity);
		auto const & impulseForce = math::toVector(m_direction) * m_speed;
		auto const & velocity = (math::toVector(motion.direction) * (motion.speed)) + impulseForce;
		motion.direction = velocity.toAngle();
		motion.speed = velocity.magnitude();
	}
	else if (m_registry.has<comp::AirMotion>(m_entity))
	{
		auto & motion = m_registry.get<comp::AirMotion>(m_entity);
		auto const & impulseForce = math::toVector(m_direction) * (m_speed * motion.lateralConstraint);
		auto const & velocity = (math::toVector(motion.direction) * (motion.speed)) + impulseForce;
		motion.direction = velocity.toAngle();
		motion.speed = velocity.magnitude();
	}
}
