#include "stdafx.h"
#include "EntityFactory.h"
#include "singletons/RegistrySingleton.h"
#include "singletons/ResourceManagerSingleton.h"

app::fact::EntityFactory::EntityFactory()
	: m_registry(app::sin::Registry::get())
	, m_resourceManager(app::sin::ResourceManager::get())
{
}

app::Entity const app::fact::EntityFactory::create()
{
	return m_registry.create();
}
