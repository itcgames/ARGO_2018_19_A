#include "stdafx.h"
#include "DashSystem.h"
#include "components/Motion.h"
#include "components/Dash.h"
#include "components/AirMotion.h"
#include "components/Location.h"

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
			dash.speed = 0;
			m_registry.remove<comp::Dash>(entity);
			m_registry.assign<comp::AirMotion>(entity);
		}
		location.position += velocity * dt.count();
	});
}
