#include "stdafx.h"
#include "HealthSystem.h"

#include "components/Health.h"
#include "components/Input.h"
#include "components/Destructible.h"
#include "components/Destroy.h"
#include "components/Enemy.h"

void app::sys::HealthSystem::update(app::time::seconds const & dt)
{
	auto inputView = m_registry.view<comp::Health, comp::Input>();
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
			else if (enemyView.contains(entity))
			{
				auto destroy = comp::Destroy();
				m_registry.assign<decltype(destroy)>(entity, std::move(destroy));
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