#include "stdafx.h"
#include "EntityState.h"
#include "singletons/RegistrySingleton.h"

app::fsm::sta::EntityState::EntityState(app::Entity const entity)
	: BaseState()
	, m_entity(entity)
	, m_registry(app::sin::Registry::get())
{
}
