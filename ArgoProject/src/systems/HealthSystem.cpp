#include "stdafx.h"
#include "HealthSystem.h"

#include "components/Health.h"
#include "components/Input.h"
#include "components/Destructible.h"
#include "components/Destroy.h"
#include "components/Enemy.h"
#include "components/AI.h"

void app::sys::HealthSystem::update(app::time::seconds const & dt)
{
	auto inputView = m_registry.view<comp::Health, comp::Input>();
	auto aiView = m_registry.view<comp::Health, comp::AI>();
	auto enemyView = m_registry.view<comp::Health, comp::Enemy>();

	m_registry.view<comp::Health>()
		.each([&, this](app::Entity const entity, comp::Health & health)
	{
		if (health.health <= 0)
		{
			if (inputView.contains(entity))
			{
				m_registry.remove<comp::Input>(entity);
			}
			else if (aiView.contains(entity))
			{
				m_registry.remove<comp::AI>(entity);
			}
			else if (enemyView.contains(entity))
			{
				m_registry.assign<comp::Destroy>(entity);
			}
		}
	});
	checkDestructibleHealth();
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
				if (m_registry.valid(target)) { m_registry.assign<comp::Destroy>(target); }
			}
			if (m_registry.valid(entity)) 
			{
				m_registry.assign<comp::Destroy>(entity);
			}
		}
	});
}