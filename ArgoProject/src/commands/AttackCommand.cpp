#include "stdafx.h"
#include "AttackCommand.h"
#include "utilities/cute_c2.h"
#include "components/CharacterType.h"
#include "components/Destroy.h"
#include "components/Collision.h"

app::cmnd::AttackCommand::AttackCommand(app::Entity const _entity)
	: m_entity(_entity)
{
}

void app::cmnd::AttackCommand::execute()
{
	if (m_registry.has<comp::CharacterType>(m_entity))
	{
		auto& typeComp = m_registry.get<comp::CharacterType>(m_entity);
		const comp::CharacterType::Type & typeEnum = typeComp.m_type;

		switch (typeEnum)
		{
		case comp::CharacterType::Type::AXE:
		{
			//auto motion = comp::AirMotion();
			//motion.speed = 0.0f;
			//motion.direction = 0.0f;
			//motion.angularSpeed = 0.0f;
			//m_registry.assign<decltype(motion)>(entity, std::move(motion));

			auto destroy = comp::Destroy();
			destroy.timeToLive = 0.5f;
			m_registry.assign<decltype(destroy)>(m_entity, std::move(destroy));

			//location
			//dimensions


			auto collision = comp::Collision();
			collision.bounds = cute::c2AABB();
			m_registry.assign<decltype(collision)>(m_entity, std::move(collision));

		}
			break;
		case comp::CharacterType::Type::BOMB:
			break;
		case comp::CharacterType::Type::DISC:
			break;
		case comp::CharacterType::Type::SWORD_LEGS:
			break;
		default:
			break;
		}
	}
}
