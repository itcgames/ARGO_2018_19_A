#include "stdafx.h"
#include "EntityFactory.h"
#include "singletons/RegistrySingleton.h"

app::fact::EntityFactory::EntityFactory()
	: m_registry(app::sin::Registry::get())
{
}

app::Entity const app::fact::EntityFactory::create()
{
	return m_registry.create();
}
