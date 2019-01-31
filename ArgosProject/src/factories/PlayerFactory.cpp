#include "stdafx.h"
#include "PlayerFactory.h"

// components
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Motion.h"
#include "components/Render.h"

app::fact::PlayerFactory::PlayerFactory(app::del::UPtrRenderer const & renderer)
	: m_texture(std::make_shared<decltype(m_texture)::element_type>())
{
	m_texture->load(renderer, "./res/image.png");
}

std::optional<app::Entity> app::fact::PlayerFactory::create()
{
	app::Entity const entity = m_registry.create();

	auto location = comp::Location();
	location.position = { 680.0f, 380.0f };
	location.orientation = 45.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = { 300.0f, 300.0f };
	dimensions.origin = dimensions.size / 2.0f;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

	auto motion = comp::Motion();
	motion.speed = 0.0f;
	motion.direction = 0.0f;
	motion.angularSpeed = 60.0f;
	m_registry.assign<decltype(motion)>(entity, std::move(motion));

	auto render = comp::Render();
	render.texture = m_texture;
	m_registry.assign<decltype(render)>(entity, std::move(render));

	return entity;
}
