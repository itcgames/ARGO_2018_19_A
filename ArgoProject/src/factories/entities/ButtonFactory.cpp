#include "stdafx.h"
#include "ButtonFactory.h"
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Motion.h"
#include "components/Text.h"
#include "components/Presseable.h"
#include "components/Render.h"
#include "components/Layer.h"
#include "components/Widget.h"
#include "components/Follow.h"
#include "components/Camera.h"

app::fact::ButtonFactory::ButtonFactory(par::ButtonFactoryParameters const & params) noexcept
	: EntityFactory()
	, m_params(params)
{
}

app::Entity const app::fact::ButtonFactory::create()
{
	auto const IGNORE_X = math::Vector2f{ 0.0f, 1.0f };

	app::Entity const entity = m_params.entity.has_value()
		? m_params.entity.value()
		: EntityFactory::create();

	auto location = comp::Location();
	location.position = m_params.position;
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = m_params.size;
	dimensions.origin = dimensions.size / 2.0f;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

	auto layer = comp::Layer();
	layer.zIndex = m_params.zIndex;
	m_registry.assign<decltype(layer)>(entity, std::move(layer));

	auto text = comp::Text();
	text.font = m_resourceManager.getFont(app::res::FontKey::Debug);
	text.string = m_params.text;
	text.border = m_params.border;
	m_registry.assign<decltype(text)>(entity, std::move(text));

	auto presseable = comp::Presseable();
	presseable.keyCommands = comp::Presseable::KeyCommands{
		std::make_pair(SDLK_RETURN, m_params.command)
	};
	presseable.mouseCommands = comp::Presseable::MouseCommands{};
	presseable.buttonCommands = comp::Presseable::ButtonCommands{
		std::make_pair(app::inp::ControllerButtonCode::SDL_CONTROLLER_BUTTON_A, m_params.command)
	};
	m_registry.assign<decltype(presseable)>(entity, std::move(presseable));

	if (m_params.follow.has_value())
	{
		auto locationView = m_registry.view<comp::Location>();
		auto cameraView = m_registry.view<comp::Camera>();
		auto const & followEntity = m_params.follow.value();
		auto follow = comp::Follow();
		follow.entity = followEntity;
		if (locationView.contains(follow.entity))
		{
			auto const & followLocation = locationView.get(follow.entity);
			follow.offset = m_params.position - followLocation.position;
		}
		else if (cameraView.contains(follow.entity))
		{
			auto const & camera = cameraView.get(follow.entity);
			follow.offset = (m_params.position - camera.center);
		}
		m_registry.assign<decltype(follow)>(entity, std::move(follow));
	}

	auto widget = comp::Widget();
	widget.state = m_params.state;
	widget.up = m_params.up;
	widget.down = m_params.down;
	widget.right = m_params.right;
	widget.left = m_params.left;
	m_registry.assign<decltype(widget)>(entity, std::move(widget));

	auto render = comp::Render();
	render.texture = m_resourceManager.getTexture(app::res::TextureKey::Debug);
	m_registry.assign<decltype(render)>(entity, std::move(render));

	return entity;
}
