#include "stdafx.h"
#include "DiscFactory.h"
#include "components/Motion.h"
#include "components/Dimensions.h"
#include "components/Location.h"
#include "components/Input.h"
#include "components/Collision.h"
#include "components/Damage.h"
#include "components/Render.h"
#include "components/Layer.h"
#include "components/Disc.h"
#include "components/Attack.h"
#include "components/Facing.h"

app::fact::DiscFactory::DiscFactory(app::Entity const _entity)
	: m_entity(_entity)
{
}

app::Entity const app::fact::DiscFactory::create()
{
	auto view = m_registry.view<comp::Facing, comp::Dimensions, comp::Location>();
	app::Entity const entity = EntityFactory::create();

	if (view.contains(m_entity))
	{
		auto[facing, dimensions, location] = view.get<comp::Facing, comp::Dimensions, comp::Location>(m_entity);

		//dimensions
		auto dimensionsComp = comp::Dimensions();
		dimensionsComp.size = { dimensions.size.x / 2, dimensions.size.y / 2 };
		dimensionsComp.origin = { dimensionsComp.size.x / 2, dimensionsComp.size.y / 2 };
		m_registry.assign<decltype(dimensionsComp)>(entity, std::move(dimensionsComp));

		//collision component
		auto collision = comp::Collision();
		collision.bounds = cute::c2AABB();
		m_registry.assign<decltype(collision)>(entity, std::move(collision));

		//disc component
		auto discCmp = comp::Disc();
		discCmp.discImpulse = 900.0f;
		discCmp.offset = { dimensions.size.x / 2 + dimensionsComp.size.x / 2 + 0.5f, 0.0f };
		discCmp.entity = m_entity;
		m_registry.assign<decltype(discCmp)>(entity, std::move(discCmp));

		//Motion
		auto motionCmp = comp::Motion();
		motionCmp.speed = discCmp.discImpulse;
		motionCmp.drag = 0.96f;
		motionCmp.dragCutoff = 0.1f;
		motionCmp.maxSpeed = 1000.0f;

		//location
		auto locationComp = comp::Location();
		if (facing.isRight)
		{
			locationComp.position = location.position + discCmp.offset;
			motionCmp.direction = 0;
		}
		else
		{
			locationComp.position = location.position - discCmp.offset;
			motionCmp.direction = 180;
		}
		locationComp.orientation = location.orientation;
		m_registry.assign<decltype(locationComp)>(entity, std::move(locationComp));
		m_registry.assign<decltype(motionCmp)>(entity, std::move(motionCmp));


		auto damage = comp::Damage();
		damage.damage = 1;
		m_registry.assign<decltype(damage)>(entity, std::move(damage));

		auto attack = comp::Attack();
		m_registry.assign<decltype(attack)>(entity, std::move(attack));


		if constexpr (DEBUG_MODE)
		{
			auto layer = comp::Layer();
			layer.zIndex = 150u;
			m_registry.assign<decltype(layer)>(entity, std::move(layer));

			auto render = comp::Render();
			render.texture = m_resourceManager.getTexture(app::res::TextureKey::DebugCollisionBox);
			m_registry.assign<decltype(render)>(entity, std::move(render));
		}
	}

	return entity;
}
