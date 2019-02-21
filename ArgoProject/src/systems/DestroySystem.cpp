#include "stdafx.h"
#include "DestroySystem.h"
#include "components/Destroy.h"

void app::sys::DestroySystem::update(app::time::seconds const & dt)
{
	for (app::Entity const entity : m_registry.view<comp::Destroy>())
	{
		m_registry.destroy(entity);
	}
}
