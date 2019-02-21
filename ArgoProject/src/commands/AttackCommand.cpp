#include "stdafx.h"
#include "AttackCommand.h"
#include "utilities/cute_c2.h"
#include "components/CharacterType.h"
#include "components/Destroy.h"
#include "components/Collision.h"
#include "components/Location.h"
#include "components/Dimensions.h"

app::cmnd::AttackCommand::AttackCommand(app::Entity const _entity)
	: m_entity(_entity)
{
}

void app::cmnd::AttackCommand::execute()
{
	if (m_registry.has<comp::CharacterType>(m_entity))
	{
		auto view = m_registry.view<comp::Location, comp::Dimensions, comp::CharacterType>();
		auto const &[location, dimensions, characterType] = view.get<comp::Location, comp::Dimensions, comp::CharacterType>(m_entity);

		switch (characterType.type)
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
			auto location = comp::Location();
			m_registry.assign<decltype(location)>(m_entity, std::move(location));

			//dimensions
			auto dimensions = comp::Dimensions();
			m_registry.assign<decltype(dimensions)>(m_entity, std::move(dimensions));


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
