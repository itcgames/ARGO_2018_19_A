#include "stdafx.h"
#include "DestructibleBlockFactory.h"
#include "utilities/cute_c2.h"

#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Render.h"
#include "components/Collision.h"
#include "components/Health.h"
#include "components/Impenetrable.h"
#include "components/Destructible.h"

app::fact::DestructibleBlockFactory::DestructibleBlockFactory(app::par::DestructibleParameters param)
	: parameters(param)
{
}

app::Entity const app::fact::DestructibleBlockFactory::create()
{
	app::Entity const entity = m_registry.create();

	app::math::Vector2f m_position = parameters.position;
	app::math::Vector2f m_size = parameters.size;

	auto location = comp::Location();
	location.position = m_position;
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = m_size;
	dimensions.origin = dimensions.size / 2.0f;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

	auto render = comp::Render();
	render.texture = m_resourceManager.getTexture(app::res::TextureKey::Debug);
	m_registry.assign<decltype(render)>(entity, std::move(render));

	auto collision = comp::Collision();
	collision.bounds = cute::c2AABB();
	m_registry.assign<decltype(collision)>(entity, std::move(collision));

	auto health = comp::Health();
	health.health = 1;
	m_registry.assign<decltype(health)>(entity, std::move(health));

	auto impenetrable = comp::Impenetrable();
	m_registry.assign<decltype(impenetrable)>(entity, std::move(impenetrable));

	auto destructible = comp::Destructible();
	if (parameters.attachedArea.has_value())
	{
		destructible.attatchedArea = parameters.attachedArea.value();
	}
	m_registry.assign<decltype(destructible)>(entity, std::move(destructible));

	return entity;	
}
