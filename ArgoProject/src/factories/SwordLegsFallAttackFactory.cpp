﻿#include "stdafx.h"
#include "SwordLegsFallAttackFactory.h"
#include "components/Destroy.h"
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Collision.h"
#include "components/Follow.h"
#include "components/Render.h"
#include "components/Layer.h"
#include "components/Input.h"
#include "components/Damage.h"
#include "components/Attack.h"
#include "components/DashAttack.h"

app::fact::SwordLegsFallAttackFactory::SwordLegsFallAttackFactory(app::Entity const _entity)
	: m_entity(_entity)
{
}

app::Entity const app::fact::SwordLegsFallAttackFactory::create()
{
	auto view = m_registry.view<comp::Input, comp::Dimensions, comp::Location>();
	app::Entity const entity = EntityFactory::create();

	if (view.contains(m_entity))
	{
		auto[input, dimensions, location] = view.get<comp::Input, comp::Dimensions, comp::Location>(m_entity);

		//destroy
		auto destroyComp = comp::Destroy();
		destroyComp.timeToLive = 0.2f;
		m_registry.assign<decltype(destroyComp)>(entity, std::move(destroyComp));


		//dimensions
		auto dimensionsComp = comp::Dimensions();
		dimensionsComp.size = { dimensions.size.x, 10.0f };
		dimensionsComp.origin = { dimensionsComp.size.x / 2, dimensionsComp.size.y / 2 };
		m_registry.assign<decltype(dimensionsComp)>(entity, std::move(dimensionsComp));

		//collision component
		auto collision = comp::Collision();
		collision.bounds = cute::c2AABB();
		m_registry.assign<decltype(collision)>(entity, std::move(collision));

		//follow entity component
		auto followEnt = comp::Follow();
		followEnt.entity = m_entity;
		followEnt.offset = { 0.0f, dimensions.size.y / 2 + dimensionsComp.size.y / 2 + 0.5f };
		m_registry.assign<decltype(followEnt)>(entity, std::move(followEnt));

		//location
		auto locationComp = comp::Location();
		locationComp.position = location.position + followEnt.offset;

		locationComp.orientation = location.orientation;
		m_registry.assign<decltype(locationComp)>(entity, std::move(locationComp));

		auto damage = comp::Damage();
		damage.damage = 1;
		m_registry.assign<decltype(damage)>(entity, std::move(damage));

		auto attack = comp::Attack();
		m_registry.assign<decltype(attack)>(entity, std::move(attack));

		auto dashAttack = comp::DashAttack();
		m_registry.assign<decltype(dashAttack)>(entity, std::move(dashAttack));

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
