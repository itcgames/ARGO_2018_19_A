#include "stdafx.h"
#include "BackgroundImageFactory.h"
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Layer.h"
#include "components/Render.h"

app::fact::BackgroundImageFactory::BackgroundImageFactory(
	  math::Vector2f const & position
	, math::Vector2f const & size
	, math::Vector2f const & origin
	, app::res::TextureKey const & textureKey
	, std::uint32_t const & zIndex
)
	: EntityFactory()
	, m_position(position)
	, m_size(size)
	, m_origin(origin)
	, m_textureKey(textureKey)
	, m_zIndex(zIndex)
{
}

app::Entity const app::fact::BackgroundImageFactory::create()
{
	app::Entity const entity = m_registry.create();

	auto location = comp::Location();
	location.position = m_position;
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = m_size;
	dimensions.origin = m_origin;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

	auto layer = comp::Layer();
	layer.zIndex = m_zIndex;
	m_registry.assign<decltype(layer)>(entity, std::move(layer));

	auto render = comp::Render();
	render.texture = m_resourceManager.getTexture(m_textureKey);
	m_registry.assign<decltype(render)>(entity, std::move(render));

	return entity;
}
