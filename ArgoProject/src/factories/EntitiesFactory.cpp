#include "stdafx.h"
#include "EntitiesFactory.h"
#include "singletons/RegistrySingleton.h"
#include "singletons/ResourceManagerSingleton.h"

app::fact::EntitiesFactory::EntitiesFactory()
	: BaseFactory()
	, m_registry(app::sin::Registry::get())
	, m_resourceManager(app::sin::ResourceManager::get())
	, m_entityFactory()
{
}
