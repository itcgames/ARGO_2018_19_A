#include "stdafx.h"
#include "DashCommand.h"
#include "components/Dash.h"
#include "components/Motion.h"
#include "components/AirMotion.h"

app::cmnd::DashCommand::DashCommand(app::Entity const _entity)
	: m_entity(_entity)
{
}

void app::cmnd::DashCommand::execute()
{
	if (!m_registry.has<comp::Dash>(m_entity))
	{
		if (m_registry.has<comp::Motion>(m_entity))
		{
			m_registry.remove<comp::Motion>(m_entity);
		}
		else if (m_registry.has<comp::AirMotion>(m_entity))
		{
			m_registry.remove<comp::AirMotion>(m_entity);
		}
		auto dash = comp::Dash();
		dash.direction = 0;
		dash.drag = 0.8f;
		dash.dragCutoff = 10.0f;
		dash.speed = 500.0f;
		m_registry.assign<decltype(dash)>(m_entity, std::move(dash));
	}
}
