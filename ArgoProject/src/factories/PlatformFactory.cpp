#include "stdafx.h"
#include "utilities/cute_c2.h"
#include "PlatformFactory.h"

#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Animator.h"
#include "components/Render.h"
#include "components/Collision.h"
#include "components/Platform.h"

app::fact::PlatformFactory::PlatformFactory(app::math::Vector2f position, app::math::Vector2f size)
	:m_texture(std::make_shared<decltype(m_texture)::element_type>()), m_position(position), m_size(size)
{
	m_texture->load(m_renderer, "./res/image.png");
}

app::Entity const app::fact::PlatformFactory::create()
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

	auto render = comp::Render();
	render.texture = m_texture;
	m_registry.assign<decltype(render)>(entity, std::move(render));

	auto collision = comp::Collision();
	collision.bounds = cute::c2AABB();
	m_registry.assign<decltype(collision)>(entity, std::move(collision));

	auto platform = comp::Platform();
	m_registry.assign<decltype(platform)>(entity, std::move(platform));

	return entity;
}