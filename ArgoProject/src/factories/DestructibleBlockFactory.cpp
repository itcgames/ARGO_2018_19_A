﻿#include "stdafx.h"
#include "DestructibleBlockFactory.h"
#include "utilities/cute_c2.h"
#include "factories/entities/ImageFactory.h"

#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Layer.h"
#include "components/Render.h"
#include "components/Collision.h"
#include "components/Health.h"
#include "components/Impenetrable.h"
#include "components/Destructible.h"
#include "components/Layer.h"
#include "components/Tiled.h"


app::fact::DestructibleBlockFactory::DestructibleBlockFactory(app::par::DestructibleParameters param)
	: parameters(param)
{
}

std::vector<app::Entity> app::fact::DestructibleBlockFactory::create()
{
	app::math::Vector2f m_position = parameters.position;
	app::math::Vector2f m_size = parameters.size;
	app::math::Vector2f m_sizeOfTile = parameters.tileSize;
	app::math::Vector2i m_numberOfTiles = parameters.numberOfTiles;
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
	app::Entity const entity = m_registry.create();


	auto location = comp::Location();
	location.position = m_position;
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = m_size;
	dimensions.origin = dimensions.size / 2.0f;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

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
		destructible.attachedArea = parameters.attachedArea.value();
	}
	m_registry.assign<decltype(destructible)>(entity, std::move(destructible));

	auto tiled = comp::Tiled();
	tiled.tiles = entities;
	m_registry.assign<decltype(tiled)>(entity, std::move(tiled));

	entities.push_back(entity);

	return entities;	
}
