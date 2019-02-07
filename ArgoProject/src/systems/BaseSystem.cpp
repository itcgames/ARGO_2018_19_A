#include "stdafx.h"
#include "BaseSystem.h"
#include "singletons/RegistrySingleton.h"

app::sys::BaseSystem::BaseSystem()
	: m_registry(app::sin::Registry::get())
{
}
