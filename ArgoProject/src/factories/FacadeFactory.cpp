#include "stdafx.h"
#include "FacadeFactory.h"
#include "utilities/cute_c2.h"
#include "factories/entities/ImageFactory.h"

#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Layer.h"
#include "components/Render.h"
#include "components/Layer.h"
#include "components/Facade.h"
#include "components/Tiled.h"

app::fact::FacadeFactory::FacadeFactory(app::math::Vector2f const & pos, app::math::Vector2f const & size, app::math::Vector2i const & numberOfTiles)
	: m_position(pos), m_sizeOfTile(size), m_numberOfTiles(numberOfTiles)
{
}

std::vector<app::Entity> app::fact::FacadeFactory::create()
{
	auto entities = std::vector<app::Entity>();

	auto const size = m_sizeOfTile * static_cast<math::Vector2f>(m_numberOfTiles);
	auto const origin = size / 2.0f;

	auto const sizeOfTile = m_sizeOfTile;
	auto const originOfTile = sizeOfTile / 2.0f;
	auto const zIndex = 140u;
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
	app::Entity const entity = m_registry.create();

	auto location = comp::Location();
	location.position = m_position;
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = m_sizeOfTile;
	dimensions.origin = dimensions.size / 2.0f;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

	auto facade = comp::Facade();
	m_registry.assign<decltype(facade)>(entity, std::move(facade));

	auto tiled = comp::Tiled();
	tiled.tiles = entities;
	m_registry.assign<decltype(tiled)>(entity, std::move(tiled));

	entities.push_back(entity);

	return entities;
}