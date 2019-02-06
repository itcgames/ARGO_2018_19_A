#include "stdafx.h"
#include "EntitiesFactory.h"
#include "singletons/RegistrySingleton.h"
#include "singletons/WindowSingleton.h"

app::fact::EntitiesFactory::EntitiesFactory()
	: BaseFactory()
	, m_registry(app::sin::Registry::get())
	, m_renderer(app::sin::Window::get().getRenderer())
	, m_entityFactory()
{
}
