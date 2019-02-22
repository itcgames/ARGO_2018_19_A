#include "stdafx.h"
#include "GoalFactory.h"
#include "utilities/cute_c2.h"

#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Render.h"
#include "components/Collision.h"
#include "components/Goal.h"
#include "components/Layer.h"

app::fact::GoalFactory::GoalFactory(math::Vector2f const & position, math::Vector2f const & size)
	: m_position(position), m_size(size)
{
}

app::Entity const app::fact::GoalFactory::create()
{
	app::Entity const entity = m_registry.create();

	auto location = comp::Location();
	location.position = m_position;
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = m_size;
	dimensions.origin = dimensions.size / 2.0f;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

	auto layer = comp::Layer();
	layer.zIndex = 120u;
	m_registry.assign<decltype(layer)>(entity, std::move(layer));

	auto render = comp::Render();
	render.texture = m_resourceManager.getTexture(app::res::TextureKey::Debug);
	m_registry.assign<decltype(render)>(entity, std::move(render));

	auto collision = comp::Collision();
	collision.bounds = cute::c2AABB();
	m_registry.assign<decltype(collision)>(entity, std::move(collision));

	auto goal = comp::Goal();
	m_registry.assign<decltype(goal)>(entity, std::move(goal));

	return entity;
}
