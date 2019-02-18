#include "stdafx.h"
#include "ButtonFactory.h"
#include "utilities/variant.h"
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Motion.h"
#include "components/Text.h"
#include "components/Presseable.h"
#include "components/Render.h"

app::fact::ButtonFactory::ButtonFactory(par::ButtonFactoryParameters const & params) noexcept
	: EntityFactory()
	, m_params(params)
{
}

app::Entity const app::fact::ButtonFactory::create()
{
	app::Entity const entity = EntityFactory::create();

	auto location = comp::Location();
	location.position = m_params.position;
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = m_params.size;
	dimensions.origin = dimensions.size / 2.0f;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

	auto text = comp::Text();
	text.font = m_resourceManager.getFont(app::res::FontKey::Debug);
	text.string = m_params.text;
	text.border = m_params.border;
	m_registry.assign<decltype(text)>(entity, std::move(text));

	auto presseable = comp::Presseable();
	presseable.keyCommands = comp::Presseable::KeyCommands{
		std::make_pair(SDLK_b, m_params.command)
	};
	presseable.mouseCommands = comp::Presseable::MouseCommands{
		std::make_pair(SDL_BUTTON_LEFT, m_params.command)
	};
	presseable.buttonCommands = comp::Presseable::ButtonCommands{
		std::make_pair(app::inp::ControllerButtonCode::SDL_CONTROLLER_BUTTON_A, m_params.command)
	};
	m_registry.assign<decltype(presseable)>(entity, std::move(presseable));

	auto render = comp::Render();
	render.texture = m_resourceManager.getTexture(app::res::TextureKey::Debug);
	m_registry.assign<decltype(render)>(entity, std::move(render));

	return entity;
}
