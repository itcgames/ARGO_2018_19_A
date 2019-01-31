#include "stdafx.h"
#include "BaseSystem.h"
#include "Registry.h"

app::sys::BaseSystem::BaseSystem()
	: m_registry(app::Reg::get())
{
}
