#include "stdafx.h"
#include "BombAttackFactory.h"
#include "components/Input.h"
#include "components/Dimensions.h"
#include "components/Location.h"
#include "components/Collision.h"
#include "components/Damage.h"
#include "components/Attack.h"
#include "components/Layer.h"
#include "components/Render.h"
#include "components/AirMotion.h"
#include "components/Bomb.h"
#include "components/Facing.h"

app::fact::BombAttackFactory::BombAttackFactory(app::Entity const entity)
	: m_entity(entity)
{
}

app::Entity const app::fact::BombAttackFactory::create()
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

		//bomb component
		auto bomb = comp::Bomb();
		bomb.impulse = 1000.0f;
		m_registry.assign<decltype(bomb)>(entity, std::move(bomb));

		//air motion comp
		auto airMotion = comp::AirMotion();
		airMotion.speed = bomb.impulse;
		airMotion.angularSpeed = 0;

		//location
		auto locationComp = comp::Location();
		if (facing.isRight)
		{
			locationComp.position = { location.position.x + dimensions.size.x, location.position.y};
			airMotion.direction = 0;
		}
		else
		{
			locationComp.position = { location.position.x - dimensions.size.x, location.position.y};
			airMotion.direction = 180;
		}
		locationComp.orientation = location.orientation;
		m_registry.assign<decltype(locationComp)>(entity, std::move(locationComp));
		m_registry.assign<decltype(airMotion)>(entity, std::move(airMotion));

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
