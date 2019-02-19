#include "stdafx.h"
#include "HealthSystem.h"

#include "components/Health.h"
#include "components/Input.h"

void app::sys::HealthSystem::update(app::time::seconds const & dt)
{
	checkPlayerHealth(dt);
}

void app::sys::HealthSystem::checkPlayerHealth(app::time::seconds const & dt)
{
	m_registry.view<comp::Health, comp::Input>()
		.each([&, this](app::Entity const entity, comp::Health & health, comp::Input const & input)
	{
		if (health.health <= 0)
		{
			m_registry.remove<comp::Input>(entity);
		}
	});
}