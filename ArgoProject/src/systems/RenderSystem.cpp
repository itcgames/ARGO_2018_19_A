#include "stdafx.h"
#include "RenderSystem.h"
#include "singletons/WindowSingleton.h"

// components
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Render.h"
#include "components/Text.h"
#include "components/Layer.h"
#include "components/Camera.h"

app::sys::RenderSystem::RenderSystem()
	: BaseSystem()
	, m_window(app::sin::Window::get())
{
	entt::connect<comp::Layer>(m_registry.construction<comp::Render>());
	entt::connect<comp::Layer>(m_registry.construction<comp::Text>());
	m_registry.construction<comp::Layer>().connect<app::sys::RenderSystem, &app::sys::RenderSystem::onLayerConstruction>(this);
	m_registry.prepare<comp::Location, comp::Dimensions, comp::Layer, comp::Render>();
	m_registry.prepare<comp::Location, comp::Dimensions, comp::Layer, comp::Text>();
}

void app::sys::RenderSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Camera>()
		.each([&, this](app::Entity const camEntity, comp::Camera & camera)
	{
		m_view.position = camera.center;
		m_view.size = camera.size;
		m_window.setView(m_view);
		auto renderView = m_registry.view<comp::Layer, comp::Location, comp::Dimensions, comp::Render>(entt::persistent_t());
		auto textView = m_registry.view<comp::Layer, comp::Location, comp::Dimensions, comp::Text>(entt::persistent_t());
		m_registry.view<comp::Layer>()
			.each([&, this](app::Entity const entity, comp::Layer & layer)
		{
			if (renderView.contains(entity))
			{
				auto [location, dimensions, render] = renderView.get<comp::Location, comp::Dimensions, comp::Render>(entity);
				m_renderRect.setPosition(location.position);
				m_renderRect.setRotation(location.orientation);
				m_renderRect.setSize(dimensions.size);
				m_renderRect.setOrigin(dimensions.origin);
				m_renderRect.setTexture(render.texture);
				m_renderRect.setSourceRect(render.source);
				m_window.render(m_renderRect);
			}
			if (textView.contains(entity))
			{
				auto [location, dimensions, text] = textView.get<comp::Location, comp::Dimensions, comp::Text>(entity);
				m_renderText.setPosition(location.position);
				m_renderText.setRotation(location.orientation);
				m_renderText.setSize(dimensions.size - (text.border * 2.0f));
				m_renderText.setOrigin(dimensions.origin - text.border);
				m_renderText.setFont(text.font);
				m_renderText.setText(text.string);
				m_renderText.setColor(text.color);
				m_window.render(m_renderText);
			}
		});
		m_window.resetView();
	});
}

void app::sys::RenderSystem::onLayerConstruction(app::Registry & registry, app::Entity const entity)
{
	registry.sort<comp::Layer>([](comp::Layer const & lhs, comp::Layer const & rhs)
	{
		return lhs.zIndex < rhs.zIndex;
	});
}
