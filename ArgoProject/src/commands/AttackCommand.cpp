#include "stdafx.h"
#include "AttackCommand.h"
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/CharacterType.h"
#include "factories/entities/AxeAttackFactory.h"


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
			auto axeAttackFactory = fact::AxeAttackFactory(m_entity);
			axeAttackFactory.create();
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
