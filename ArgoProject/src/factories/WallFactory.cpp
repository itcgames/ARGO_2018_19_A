#include "stdafx.h"
#include "WallFactory.h"
#include "utilities/cute_c2.h"
#include "factories/entities/ImageFactory.h"

#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Animator.h"
#include "components/Render.h"
#include "components/Collision.h"
#include "components/Impenetrable.h"
#include "components/Layer.h"

app::fact::WallFactory::WallFactory(app::math::Vector2f const & pos, app::math::Vector2f const & size, app::math::Vector2i const & numberOfTiles)
	: m_position(pos), m_sizeOfTile(size), m_numberOfTiles(numberOfTiles)
{
}

std::vector<app::Entity> app::fact::WallFactory::create()
{
	auto entities = std::vector<app::Entity>();

	auto const size = m_sizeOfTile * static_cast<math::Vector2f>(m_numberOfTiles);
	auto const origin = size / 2.0f;

	auto const sizeOfTile = m_sizeOfTile;
	auto const originOfTile = sizeOfTile / 2.0f;
	auto const zIndex = 130u;
	auto const textureKey = app::res::TextureKey::LevelWall;
	auto const startPosition = m_position - origin + originOfTile;
	auto position = startPosition;
	auto tileFactory = fact::ImageFactory(position, sizeOfTile, originOfTile, textureKey, zIndex);
	for (std::int32_t x = 0; x < m_numberOfTiles.x; ++x)
	{
		for (std::int32_t y = 0; y < m_numberOfTiles.y; ++y)
		{
			position = startPosition + (sizeOfTile * math::Vector2f{ x, y });
			entities.push_back(tileFactory.create());
		}
	}

	{
		app::Entity const wallEntity = m_registry.create();

		auto location = comp::Location();
		location.position = m_position;
		location.orientation = 0.0f;
		m_registry.assign<decltype(location)>(wallEntity, std::move(location));

		auto dimensions = comp::Dimensions();
		dimensions.size = size;
		dimensions.origin = origin;
		m_registry.assign<decltype(dimensions)>(wallEntity, std::move(dimensions));

		//auto layer = comp::Layer();
		//layer.zIndex = 130u;
		//m_registry.assign<decltype(layer)>(wallEntity, std::move(layer));

		//auto render = comp::Render();
		//render.texture = m_resourceManager.getTexture(app::res::TextureKey::LevelWall);
		//m_registry.assign<decltype(render)>(wallEntity, std::move(render));

		auto collision = comp::Collision();
		collision.bounds = cute::c2AABB();
		m_registry.assign<decltype(collision)>(wallEntity, std::move(collision));

		auto impenetrable = comp::Impenetrable();
		m_registry.assign<decltype(impenetrable)>(wallEntity, std::move(impenetrable));

		entities.push_back(wallEntity);
	}

	return entities;
}