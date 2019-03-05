#include "stdafx.h"
#include "AttackCommand.h"
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/CharacterType.h"
#include "components/Input.h"
#include "factories/entities/AxeAttackFactory.h"
#include "factories/DiscFactory.h"
#include "factories/BombAttackFactory.h"


app::cmnd::AttackCommand::AttackCommand(app::Entity const _entity)
	: m_entity(_entity)
{
}

void app::cmnd::AttackCommand::execute()
{
	auto characterTypeView = m_registry.view<comp::Location, comp::Dimensions, comp::CharacterType, comp::Input>(entt::persistent_t());
	if (characterTypeView.contains(m_entity))
	{
		auto const &[location, dimensions, characterType, input] = characterTypeView.get<comp::Location, comp::Dimensions, comp::CharacterType, comp::Input>(m_entity);

		switch (characterType.type)
		{
		case comp::CharacterType::Type::AXE:
		{
			auto axeAttackFactory = fact::AxeAttackFactory(m_entity);
			axeAttackFactory.create();
		}
			break;
		case comp::CharacterType::Type::BOMB:
		{
			auto bombAttackFactory = fact::BombAttackFactory(m_entity);
			bombAttackFactory.create();
		}
			break;
		case comp::CharacterType::Type::DISC:
		{
			if (input.canAttack)
			{
				auto discFactory = fact::DiscFactory(m_entity);
				discFactory.create();
				input.canAttack = false;
			}
		}
			break;
		case comp::CharacterType::Type::SWORD_LEGS:
			break;
		default:
			break;
		}
	}
}
