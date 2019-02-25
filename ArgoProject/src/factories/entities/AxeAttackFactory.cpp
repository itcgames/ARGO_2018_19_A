#include "stdafx.h"
#include "AxeAttackFactory.h"
#include "components/Destroy.h"
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Collision.h"
#include "components/FollowEntity.h"
#include "components/Render.h"
#include "components/Layer.h"
#include "components/Input.h"
#include "components/Damage.h"
#include "components/Attack.h"

app::fact::AxeAttackFactory::AxeAttackFactory(app::Entity const _entity)
	: m_entity(_entity)
{
}

app::Entity const app::fact::AxeAttackFactory::create()
{
	auto view = m_registry.view<comp::Input, comp::Dimensions, comp::Location>();
	app::Entity const entity = EntityFactory::create();

	if (view.contains(m_entity))
	{
		auto[input, dimensions, location] = view.get<comp::Input, comp::Dimensions, comp::Location>(m_entity);

		auto destroy = comp::Destroy();
		destroy.timeToLive = 0.5f;
		m_registry.assign<decltype(destroy)>(entity, std::move(destroy));


		//dimensions
		auto dimensionsComp = comp::Dimensions();
		dimensionsComp.size = { dimensions.size.x / 2, 100.0f };
		dimensionsComp.origin = { dimensionsComp.size.x / 2, dimensionsComp.size.y / 2 };
		m_registry.assign<decltype(dimensionsComp)>(entity, std::move(dimensionsComp));

		//collision component
		auto collision = comp::Collision();
		collision.bounds = cute::c2AABB();
		m_registry.assign<decltype(collision)>(entity, std::move(collision));

		//follow entity component
		auto followEnt = comp::FollowEntity();
		followEnt.entity = m_entity;
		followEnt.offset = { dimensions.size.x / 2 + dimensionsComp.size.x / 2 + 0.5f, 0.0f };
		m_registry.assign<decltype(followEnt)>(entity, std::move(followEnt));

		//location
		auto locationComp = comp::Location();
		if (input.isRight)
		{
			locationComp.position = location.position + followEnt.offset;
		}
		else
		{
			locationComp.position = location.position - followEnt.offset;
		}
		locationComp.orientation = location.orientation;
		m_registry.assign<decltype(locationComp)>(entity, std::move(locationComp));

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
