#include "stdafx.h"
#include "JumpCommand.h"
#include "components/Motion.h"
#include "components/AirMotion.h"
#include "components/Input.h"
#include "components/Dash.h"

app::cmnd::JumpCommand::JumpCommand(app::Entity const _entity, float _force)
	: m_entity(_entity)
	, m_force(_force)
{
}

void app::cmnd::JumpCommand::execute()
{
	auto& input = m_registry.get<comp::Input>(m_entity);
	//If player tries jumping while in air
	if (m_registry.has<comp::AirMotion>(m_entity))
	{
		auto & airMotion = m_registry.get<comp::AirMotion>(m_entity);
		if (input.m_canDoubleJump)
		{
			auto impulse = math::Vector2f(0.0f, -1.0f) * m_force;
			auto const & velocity = (math::toVector(airMotion.direction) * airMotion.speed);
			auto velActual = velocity;
			velActual.y = 0;
			velActual += impulse;
			airMotion.direction = velActual.toAngle();
			airMotion.speed = velActual.magnitude();
			input.m_canDoubleJump = false;
		}
	}
	else //if player tries jumping from ground
	{
		
		if (m_registry.has<comp::Motion>(m_entity)) //if player on ground
		{
			auto & motion = m_registry.get<comp::Motion>(m_entity);
			auto impulse = math::Vector2f(0.0f, -1.0f) * m_force;
			auto const & velocity = (math::toVector(motion.direction) * motion.speed);
			auto velActual = velocity;
			velActual.y = 0;
			velActual += impulse;
			motion.direction = velActual.toAngle();
			motion.speed = velActual.magnitude();

			auto airMotion = comp::AirMotion();
			airMotion.speed = motion.speed;
			airMotion.direction = motion.direction;
			airMotion.angularSpeed = motion.angularSpeed;
			airMotion.maxSpeed = 500.0f;
			m_registry.assign<comp::AirMotion>(m_entity, std::move(airMotion));
			m_registry.remove<comp::Motion>(m_entity);
		}
		else if (m_registry.has<comp::Dash>(m_entity)) //if player currently in the middle of a dash
		{
			auto & motion = m_registry.get<comp::Dash>(m_entity);
			auto impulse = math::Vector2f(0.0f, -1.0f) * m_force;
			auto const & velocity = (math::toVector(motion.direction) * motion.speed);
			auto velActual = velocity;
			velActual.y = 0;
			velActual += impulse;
			motion.direction = velocity.toAngle();
			motion.speed = velocity.magnitude();
			motion.direction = velActual.toAngle();
			motion.speed = velActual.magnitude();

			auto airMotion = comp::AirMotion();
			airMotion.speed = motion.speed;
			airMotion.direction = motion.direction;
			airMotion.maxSpeed = 500.0f;
			m_registry.assign<comp::AirMotion>(m_entity, std::move(airMotion));
			m_registry.remove<comp::Dash>(m_entity);
			input.m_canDoubleJump = false;
		}

	}
	
}
