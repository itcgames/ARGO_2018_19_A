#include "stdafx.h"
#include "BombExplosionSystem.h"
#include "components/Bomb.h"
#include "components/AirMotion.h"
#include "components/Destroy.h"

void app::sys::BombExplosionSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Bomb>()
		.each([&, this](app::Entity const bombEntity, comp::Bomb& bombComp)
	{
		if (bombComp.exploded)
		{
			//if air motion exists but bomb exploded remove air comp
			//and add destroy comp
			auto airCompView = m_registry.view<comp::AirMotion>();
			if (airCompView.contains(bombEntity))
			{
				m_registry.remove<comp::AirMotion>(bombEntity);
				auto destroy = comp::Destroy();
				destroy.timeToLive = 0.5f;
				m_registry.assign<decltype(destroy)>(bombEntity, std::move(destroy));
			}
		}
	});
}
