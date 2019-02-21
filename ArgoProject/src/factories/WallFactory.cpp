#include "stdafx.h"
#include "utilities/cute_c2.h"
#include "WallFactory.h"

#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Animator.h"
#include "components/Render.h"
#include "components/Collision.h"
#include "components/Impenetrable.h"
#include "components/Layer.h"

app::fact::WallFactory::WallFactory(app::math::Vector2f const & pos, app::math::Vector2f const & size)
	: m_position(pos), m_size(size)
{
}

app::Entity const app::fact::WallFactory::create()
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
	layer.zIndex = 130u;
	m_registry.assign<decltype(layer)>(entity, std::move(layer));

	auto render = comp::Render();
	render.texture = m_resourceManager.getTexture(app::res::TextureKey::Debug);
	m_registry.assign<decltype(render)>(entity, std::move(render));

	auto collision = comp::Collision();
	collision.bounds = cute::c2AABB();
	m_registry.assign<decltype(collision)>(entity, std::move(collision));

	auto impenetrable = comp::Impenetrable();
	m_registry.assign<decltype(impenetrable)>(entity, std::move(impenetrable));

	return entity;
}