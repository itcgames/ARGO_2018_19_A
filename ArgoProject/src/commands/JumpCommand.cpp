#include "stdafx.h"
#include "JumpCommand.h"
#include "components/Motion.h"
#include "components/AirMotion.h"
#include "components/Input.h"
#include "components/Dash.h"
#include "components/DoubleJump.h"
#include "components/Dash.h"

app::cmnd::JumpCommand::JumpCommand(app::Entity const _entity, float _force)
	: m_entity(_entity)
	, m_force(_force)
{
}

void app::cmnd::JumpCommand::execute()
{
	auto& doubleJump = m_registry.get<comp::DoubleJump>(m_entity);
	//If player tries jumping while in air
	if (m_registry.has<comp::AirMotion>(m_entity))
	{
		auto & airMotion = m_registry.get<comp::AirMotion>(m_entity);
		if (doubleJump.canDoubleJump)
		{
			auto const & impulse = math::Vector2f(0.0f, -1.0f) * m_force;
			auto const & velocity = ((math::toVector(airMotion.direction) * airMotion.speed) * math::Vector2f(1.0f, 0.0f)) + impulse;
			airMotion.direction = velocity.toAngle();
			airMotion.speed = velocity.magnitude();
			doubleJump.canDoubleJump = false;
		}
	}
	else //if player tries jumping from ground
	{
		
		if (m_registry.has<comp::Motion>(m_entity)) //if player on ground
		{
			auto & motion = m_registry.get<comp::Motion>(m_entity);
			auto const & impulse = math::Vector2f(0.0f, -1.0f) * m_force;
			auto const & velocity = ((math::toVector(motion.direction) * motion.speed) * math::Vector2f(1.0f, 0.0f)) + impulse;
			motion.direction = velocity.toAngle();
			motion.speed = velocity.magnitude();

			auto airMotion = comp::AirMotion();
			airMotion.speed = motion.speed;
			airMotion.direction = motion.direction;
			airMotion.angularSpeed = motion.angularSpeed;
			m_registry.assign<comp::AirMotion>(m_entity, std::move(airMotion));
			m_registry.remove<comp::Motion>(m_entity);
		}
		else if (m_registry.has<comp::Dash>(m_entity)) //if player currently in the middle of a dash
		{
			auto & motion = m_registry.get<comp::Dash>(m_entity);
			auto const & impulse = math::Vector2f(0.0f, -1.0f) * m_force;
			auto const & velocity = ((math::toVector(motion.direction) * motion.speed) * math::Vector2f(1.0f,0.0f)) + impulse;
			motion.direction = velocity.toAngle();
			motion.speed = velocity.magnitude();

			auto airMotion = comp::AirMotion();
			airMotion.speed = motion.speed;
			airMotion.direction = motion.direction;
			m_registry.assign<comp::AirMotion>(m_entity, std::move(airMotion));
			m_registry.remove<comp::Dash>(m_entity);
			doubleJump.canDoubleJump = false;
		}

	}
	
}
