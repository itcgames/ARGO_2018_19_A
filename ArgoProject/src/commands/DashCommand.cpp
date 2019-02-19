#include "stdafx.h"
#include "DashCommand.h"
#include "singletons/KeyHandlerSingleton.h"
#include "components/Dash.h"
#include "components/Motion.h"
#include "components/AirMotion.h"
#include "components/Input.h"
#include "components/Dashable.h"

app::cmnd::DashCommand::DashCommand(app::Entity const _entity)
	: m_entity(_entity)
	, m_keyHandler(app::sin::KeyHandler::get())
{
}

void app::cmnd::DashCommand::execute()
{
	auto& input = m_registry.get<comp::Input>(m_entity);
	auto& dashable = m_registry.get<comp::Dashable>(m_entity);
	if (!m_registry.has<comp::Dash>(m_entity) && dashable.canDash)
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
		input.isRight ? dash.direction = 0 : dash.direction = -180;
		dash.drag = 0.8f;
		dash.dragCutoff = 10.0f;
		dash.speed = 5000.0f;
		m_registry.assign<decltype(dash)>(m_entity, std::move(dash));
		dashable.canDash = false;
	}
}
