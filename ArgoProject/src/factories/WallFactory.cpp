#include "stdafx.h"
#include "WallFactory.h"

#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Animator.h"
#include "components/Render.h"

app::fact::WallFactory::WallFactory(app::del::UPtrRenderer const & renderer, app::math::Vector2f v)
	: m_texture(std::make_shared<decltype(m_texture)::element_type>()), m_position(v)
{
	m_texture->load(renderer, "./res/Animations/test.png");
}

std::optional<app::Entity> app::fact::WallFactory::create() 
{
	app::Entity const entity = m_registry.create();

	auto location = comp::Location();
	location.position = m_position;
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = { 50.0f, 50.0f };
	dimensions.origin = dimensions.size / 2.0f;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

	auto render = comp::Render();
	render.texture = m_texture;
	render.source = SDL_Rect{ 0, 0, 200, 150 };
	m_registry.assign<decltype(render)>(entity, std::move(render));

	return entity;
}