#include "stdafx.h"
#include "utilities/cute_c2.h"
#include "HazardFactory.h"

#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Animator.h"
#include "components/Layer.h"
#include "components/Render.h"
#include "components/Collision.h"
#include "components/Damage.h"
#include "components/Hazard.h"
#include "components/Impenetrable.h"

#include "factories/entities/ImageFactory.h"

app::fact::HazardFactory::HazardFactory(app::math::Vector2f const & pos, app::math::Vector2f const & size, std::uint32_t const & hazardWidth)
	: m_position(pos), m_sizeOfTile(size), m_hazardWidth(hazardWidth)
{
	
}

std::vector<app::Entity> app::fact::HazardFactory::create()
{
	app::Entity const entity = m_registry.create();

	auto location = comp::Location();
	location.position = m_position;
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = m_sizeOfTile;
	dimensions.size.x *= m_hazardWidth;
	dimensions.origin = dimensions.size / 2.0f;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

	auto entities = std::vector<app::Entity>();

	auto const size = m_sizeOfTile * static_cast<math::Vector2f>(math::Vector2f(m_hazardWidth, 1));
	auto const origin = size / 2.0f;

	auto const sizeOfTile = m_sizeOfTile;
	auto const originOfTile = sizeOfTile / 2.0f;
	auto const zIndex = 130u;
	auto textureKey = app::res::TextureKey::HazardSpikes;
	auto const startPosition = m_position - origin + originOfTile;
	auto position = startPosition;
	auto tileFactory = fact::ImageFactory(position, sizeOfTile, originOfTile, textureKey, zIndex);

	for (std::int32_t x = 0; x < m_hazardWidth; ++x)
	{
		position.x = startPosition.x + (sizeOfTile.x * x);
		entities.push_back(tileFactory.create());
	}

	//auto layer = comp::Layer();
	//layer.zIndex = 120u;
	//m_registry.assign<decltype(layer)>(entity, std::move(layer));

	//auto render = comp::Render();
	//render.texture = m_resourceManager.getTexture(app::res::TextureKey::HazardSpikes);
	//m_registry.assign<decltype(render)>(entity, std::move(render));

	auto collision = comp::Collision();
	collision.bounds = cute::c2AABB();
	m_registry.assign<decltype(collision)>(entity, std::move(collision));

	auto damage = comp::Damage();
	damage.damage = 1;
	m_registry.assign<decltype(damage)>(entity, std::move(damage));

	auto hazard = comp::Hazard();
	m_registry.assign<decltype(hazard)>(entity, std::move(hazard));

	auto impenetrable = comp::Impenetrable();
	m_registry.assign<decltype(impenetrable)>(entity, std::move(impenetrable));

	entities.push_back(entity);

	return entities;
}