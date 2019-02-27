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
#include "components/FollowEntity.h"
#include "components/Layer.h"
#include "components/Render.h"


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

		//TODO: create dashing collision box
		//auto characterTypeView = m_registry.view<comp::CharacterType>();
		//if (characterTypeView.contains(m_entity))
		//{
		//	auto characterTypeComponent = m_registry.get<comp::CharacterType>(m_entity);
		//	if (characterTypeComponent.type == comp::CharacterType::Type::SWORD_LEGS)
		//	{
		//		//dimensions
		//		auto dimensionsComp = comp::Dimensions();
		//		dimensionsComp.size = { dimensions.size.x / 2, 100.0f };
		//		dimensionsComp.origin = { dimensionsComp.size.x / 2, dimensionsComp.size.y / 2 };
		//		m_registry.assign<decltype(dimensionsComp)>(entity, std::move(dimensionsComp));

		//		//collision component
		//		auto collision = comp::Collision();
		//		collision.bounds = cute::c2AABB();
		//		m_registry.assign<decltype(collision)>(entity, std::move(collision));

		//		//follow entity component
		//		auto followEnt = comp::FollowEntity();
		//		followEnt.entity = m_entity;
		//		followEnt.offset = { dimensions.size.x / 2 + dimensionsComp.size.x / 2 + 0.5f, 0.0f };
		//		m_registry.assign<decltype(followEnt)>(entity, std::move(followEnt));

		//		//location
		//		auto locationComp = comp::Location();
		//		if (input.isRight)
		//		{
		//			locationComp.position = location.position + followEnt.offset;
		//		}
		//		else
		//		{
		//			locationComp.position = location.position - followEnt.offset;
		//		}
		//		locationComp.orientation = location.orientation;
		//		m_registry.assign<decltype(locationComp)>(entity, std::move(locationComp));

		//		auto damage = comp::Damage();
		//		damage.damage = 1;
		//		m_registry.assign<decltype(damage)>(entity, std::move(damage));

		//		auto attack = comp::Attack();
		//		m_registry.assign<decltype(attack)>(entity, std::move(attack));

		//		if constexpr (DEBUG_MODE)
		//		{
		//			auto layer = comp::Layer();
		//			layer.zIndex = 150u;
		//			m_registry.assign<decltype(layer)>(entity, std::move(layer));

		//			auto render = comp::Render();
		//			render.texture = m_resourceManager.getTexture(app::res::TextureKey::DebugCollisionBox);
		//			m_registry.assign<decltype(render)>(entity, std::move(render));
		//		}
		//	}
		//}
	}
}
