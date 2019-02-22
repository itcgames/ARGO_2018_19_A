#include "stdafx.h"
#include "HealthSystem.h"

#include "components/Health.h"
#include "components/Input.h"
#include "components/Destructible.h"

void app::sys::HealthSystem::update(app::time::seconds const & dt)
{
	checkPlayerHealth();
	checkDestructibleHealth();
}

void app::sys::HealthSystem::checkPlayerHealth()
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

void app::sys::HealthSystem::checkDestructibleHealth()
{
	m_registry.view<comp::Health, comp::Destructible>()
		.each([&, this](app::Entity const entity, comp::Health & health, comp::Destructible const & destructible)
	{
		if (health.health <= 0)
		{
			if (destructible.attachedArea.has_value())
			{
				auto target = destructible.attachedArea.value();
				if (m_registry.valid(target)) { m_registry.destroy(target); }
			}
			if (m_registry.valid(entity)) 
			{
				m_registry.destroy(entity);
			}
		}
	});
}