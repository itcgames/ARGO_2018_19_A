#include "stdafx.h"
#include "ImageFactory.h"
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Layer.h"
#include "components/Render.h"
#include "components/Follow.h"
#include "components/Camera.h"

app::fact::ImageFactory::ImageFactory(
	  math::Vector2f const & position
	, math::Vector2f const & size
	, math::Vector2f const & origin
	, app::res::TextureKey const & textureKey
	, std::uint32_t const & zIndex
	, std::optional<app::Entity> const & follow
)
	: EntityFactory()
	, m_position(position)
	, m_size(size)
	, m_origin(origin)
	, m_textureKey(textureKey)
	, m_zIndex(zIndex)
	, m_follow(follow)
{
}

app::Entity const app::fact::ImageFactory::create()
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

	if (m_follow.has_value())
	{
		auto locationView = m_registry.view<comp::Location>();
		auto cameraView = m_registry.view<comp::Camera>();
		auto const & followEntity = m_follow.value();
		auto follow = comp::Follow();
		follow.entity = followEntity;
		if (locationView.contains(follow.entity))
		{
			auto const & followLocation = locationView.get(follow.entity);
			follow.offset = m_position - followLocation.position;
		}
		else if (cameraView.contains(follow.entity))
		{
			auto const & camera = cameraView.get(follow.entity);
			follow.offset = (m_position - camera.center);
		}
		m_registry.assign<decltype(follow)>(entity, std::move(follow));
	}

	auto layer = comp::Layer();
	layer.zIndex = m_zIndex;
	m_registry.assign<decltype(layer)>(entity, std::move(layer));

	auto render = comp::Render();
	render.texture = m_resourceManager.getTexture(m_textureKey);
	m_registry.assign<decltype(render)>(entity, std::move(render));

	return entity;
}
