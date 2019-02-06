#include "stdafx.h"
#include "EntitiesFactory.h"
#include "singletons/RegistrySingleton.h"

app::fact::EntitiesFactory::EntitiesFactory()
	: BaseFactory()
	, m_registry(app::sin::Registry::get())
	, m_entityFactory()
{
}
