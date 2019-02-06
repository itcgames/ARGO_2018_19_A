#include "stdafx.h"
#include "EntityFactory.h"
#include "singletons/RegistrySingleton.h"
#include "singletons/WindowSingleton.h"

app::fact::EntityFactory::EntityFactory()
	: m_registry(app::sin::Registry::get())
	, m_renderer(app::sin::Window::get().getRenderer())
{
}

app::Entity const app::fact::EntityFactory::create()
{
	return m_registry.create();
}
