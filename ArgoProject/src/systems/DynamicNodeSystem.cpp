#include "stdafx.h"
#include "DynamicNodeSystem.h"
#include "components/DynamicNodeAi.h"

void app::sys::DynamicNodeSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::DynamicNodeAi>()
		.each([&, this](app::Entity const entity, comp::DynamicNodeAi & dynamicNodeAi)
	{

	});
}
