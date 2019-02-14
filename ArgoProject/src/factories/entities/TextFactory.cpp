#include "stdafx.h"
#include "TextFactory.h"
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Text.h"

app::fact::TextFactory::TextFactory(math::Vector2f const & position, math::Vector2f const & size, std::string const & text)
	: m_position(position)
	, m_size(size)
	, m_text(text)
{
}

app::Entity const app::fact::TextFactory::create()
{
	app::Entity const entity = app::fact::EntityFactory::create();

	auto location = comp::Location();
	location.position = m_position;
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = m_size;
	dimensions.origin = dimensions.size / 2.0f;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

	auto text = comp::Text();
	text.font = m_resourceManager.getFont(app::res::FontKey::Debug);
	text.string = m_text;
	m_registry.assign<decltype(text)>(entity, std::move(text));

	return entity;
}
