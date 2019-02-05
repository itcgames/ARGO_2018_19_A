#include "stdafx.h"
#include "EntityState.h"
#include "Registry.h"

app::fsm::sta::EntityState::EntityState(app::Entity const entity)
	: BaseState()
	, m_entity(entity)
	, m_registry(app::Reg::get())
{
}
