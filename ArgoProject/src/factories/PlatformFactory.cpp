#include "stdafx.h"
#include "utilities/cute_c2.h"
#include "PlatformFactory.h"

#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Render.h"
#include "components/Collision.h"
#include "components/Platform.h"
#include "components/Layer.h"

#include "factories/entities/ImageFactory.h"

app::fact::PlatformFactory::PlatformFactory(app::math::Vector2f const & position, app::math::Vector2f const & size, std::uint32_t const & platformWidth)
	: m_position(position), m_sizeOfTile(size), m_platformWidth(platformWidth)
{
	
}

app::Entity const app::fact::PlatformFactory::create()
{
	app::Entity const entity = m_registry.create();

	auto location = comp::Location();
	location.position = m_position;
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = m_sizeOfTile;
	dimensions.size.x *= m_platformWidth;
	dimensions.origin = dimensions.size / 2.0f;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

	auto entities = std::vector<app::Entity>();

	auto const size = m_sizeOfTile * math::Vector2f(m_platformWidth, 1);
	auto const origin = size / 2.0f;

	auto const sizeOfTile = m_sizeOfTile;
	auto const originOfTile = sizeOfTile / 2.0f;
	auto const zIndex = 130u;
	auto textureKey = app::res::TextureKey::Debug;
	auto const startPosition = m_position - origin + originOfTile;
	auto position = startPosition;
	auto tileFactory = fact::ImageFactory(position, sizeOfTile, originOfTile, textureKey, zIndex);
	if (m_platformWidth == 1)
	{
		position = startPosition;
		textureKey = app::res::TextureKey::PlatformMiddle;
		entities.push_back(tileFactory.create());
	}
	else
	{
		position.x = startPosition.x;
		position.y = startPosition.y;
		textureKey = app::res::TextureKey::PlatformLeft;
		entities.push_back(tileFactory.create());

		position.x = startPosition.x + (sizeOfTile.x * (m_platformWidth - 1));
		textureKey = app::res::TextureKey::PlatformRight;
		entities.push_back(tileFactory.create());

		textureKey = app::res::TextureKey::PlatformMiddle;
		for (std::int32_t x = 1; x < m_platformWidth - 1; ++x)
		{
			position.x = startPosition.x + (sizeOfTile.x * x);
			entities.push_back(tileFactory.create());
		}
	}
	//auto layer = comp::Layer();
	//layer.zIndex = 80u;
	//m_registry.assign<decltype(layer)>(entity, std::move(layer));

	//auto render = comp::Render();
	//render.texture = m_resourceManager.getTexture(app::res::TextureKey::Debug);
	//m_registry.assign<decltype(render)>(entity, std::move(render));

	auto collision = comp::Collision();
	collision.bounds = cute::c2AABB();
	m_registry.assign<decltype(collision)>(entity, std::move(collision));

	auto platform = comp::Platform();
	m_registry.assign<decltype(platform)>(entity, std::move(platform));

	return entity;
}