#include "stdafx.h"
#include "DashCommand.h"
#include "singletons/KeyHandlerSingleton.h"
#include "components/Dash.h"
#include "components/Motion.h"
#include "components/AirMotion.h"
#include "components/Input.h"
#include "components/Dashable.h"
#include "components/CharacterType.h"
#include "components/Dimensions.h"
#include "components/Location.h"
#include "components/Collision.h"
#include "components/Follow.h"
#include "components/Layer.h"
#include "components/Render.h"
#include "components/Facing.h"
#include "factories/SwordLegsDashAttackFactory.h"


app::cmnd::DashCommand::DashCommand(app::Entity const _entity)
	: m_entity(_entity)
	, m_keyHandler(app::sin::KeyHandler::get())
{
}

void app::cmnd::DashCommand::execute()
{
	auto& dashable = m_registry.get<comp::Dashable>(m_entity);
	auto facingView = m_registry.view<comp::Facing>();
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
		if (facingView.contains(m_entity))
		{
			auto& facingComp = m_registry.get<comp::Facing>(m_entity);
			facingComp.isRight ? dash.direction = 0 : dash.direction = -180;
		}
		dash.drag = 0.8f;
		dash.dragCutoff = 10.0f;
		dash.speed = 5000.0f;
		m_registry.assign<decltype(dash)>(m_entity, std::move(dash));
		dashable.canDash = false;

		auto characterTypeView = m_registry.view<comp::CharacterType>();
		if (characterTypeView.contains(m_entity))
		{
			auto charType = m_registry.get<comp::CharacterType>(m_entity);
			if (charType.type == app::comp::CharacterType::Type::SWORD_LEGS)
			{
				auto swordDashAttackFactory = app::fact::SwordLegsDashAttackFactory(m_entity);
				swordDashAttackFactory.create();
			}
		}

	}
}
