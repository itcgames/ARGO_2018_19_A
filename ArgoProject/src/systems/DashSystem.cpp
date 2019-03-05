﻿#include "stdafx.h"
#include "DashSystem.h"
#include "components/Motion.h"
#include "components/Dash.h"
#include "components/AirMotion.h"
#include "components/Location.h"
#include "components/Input.h"
#include "components/CharacterType.h"
#include "components/Destroy.h"
#include "components/Attack.h"

void app::sys::DashSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Dash, comp::Location>()
		.each([&, this](app::Entity const entity, comp::Dash& dash, comp::Location& location)
	{
		auto const & velocity = (math::toVector(dash.direction) * dash.speed);

		if (dash.speed >= dash.dragCutoff)
		{
			//simulate drag
			dash.speed *= dash.drag;
		}
		else
		{
			auto characterTypeView = m_registry.view<comp::CharacterType>();
			if (characterTypeView.contains(entity))
			{
				auto attackView = m_registry.view<comp::Attack>();
				for (auto& attack : attackView)
				{
					m_registry.assign<comp::Destroy>(attack);
				}
			}
			dash.speed = 0;
			m_registry.remove<comp::Dash>(entity);
			auto airComp = comp::AirMotion();
			m_registry.assign<decltype(airComp)>(entity, std::move(airComp));
		}
		location.position += velocity * dt.count();
	});
}
