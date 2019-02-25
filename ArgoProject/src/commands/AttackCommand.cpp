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
	auto characterTypeView = m_registry.view<comp::Location, comp::Dimensions, comp::CharacterType>(entt::persistent_t());
	if (characterTypeView.contains(m_entity))
	{
		auto const &[location, dimensions, characterType] = characterTypeView.get<comp::Location, comp::Dimensions, comp::CharacterType>(m_entity);

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
