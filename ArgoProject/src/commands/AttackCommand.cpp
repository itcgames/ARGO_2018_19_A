#include "stdafx.h"
#include "AttackCommand.h"
#include "components/CharacterType.h"

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
