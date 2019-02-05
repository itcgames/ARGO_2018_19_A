#include "stdafx.h"
#include "CommandSystem.h"
#include "components/Commandable.h"

void app::sys::CommandSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Commandable>()
		.each([&dt, this](app::Entity const entity, comp::Commandable & commandable)
	{
		for (auto const & sptr : commandable.list) { sptr->execute(); }
		commandable.list.clear();
	});
}
