#include "stdafx.h"
#include "FacadeFactory.h"
#include "utilities/cute_c2.h"

#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Render.h"

app::fact::FacadeFactory::FacadeFactory(app::math::Vector2f const & pos, app::math::Vector2f const & size)
	: m_position(pos), m_size(size)
{
}

app::Entity const app::fact::FacadeFactory::create()
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
	render.texture = m_resourceManager.getTexture(app::res::TextureKey::Debug);
	m_registry.assign<decltype(render)>(entity, std::move(render));

	return entity;
}