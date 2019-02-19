#include "stdafx.h"
#include "RenderSystem.h"
#include "singletons/WindowSingleton.h"

// components
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Render.h"
#include "components/Modal.h"
#include "components/Camera.h"

app::sys::RenderSystem::RenderSystem()
	: BaseSystem()
	, m_window(app::sin::Window::get())
{
	m_registry.construction<comp::Render>().connect<app::sys::RenderSystem, &app::sys::RenderSystem::onRenderConstruction>(this);
	m_registry.prepare<comp::Location, comp::Dimensions, comp::Render, comp::Modal>();
}

void app::sys::RenderSystem::update(app::time::seconds const & dt)
{
	auto modalView = m_registry.view<comp::Location, comp::Dimensions, comp::Render, comp::Modal>(entt::persistent_t());
	m_registry.view<comp::Camera>()
		.each([&, this](app::Entity const camEntity, comp::Camera & camera)
	{
		m_view.position = camera.center;
		m_view.size = camera.size;
		m_window.setView(m_view);
		m_registry.view<comp::Location, comp::Dimensions, comp::Render>()
			.each([&, this](app::Entity const entity, comp::Location & location, comp::Dimensions & dimensions, comp::Render & render)
		{
			if (modalView.contains(entity)) { return; }
			m_renderRect.setPosition(location.position);
			m_renderRect.setRotation(location.orientation);
			m_renderRect.setSize(dimensions.size);
			m_renderRect.setOrigin(dimensions.origin);
			m_renderRect.setTexture(render.texture);
			m_renderRect.setSourceRect(render.source);
			m_window.render(m_renderRect);
		});
		m_window.resetView();
	});
}

void app::sys::RenderSystem::onRenderConstruction(app::Registry & registry, app::Entity entity)
{
	registry.sort<comp::Render>([](comp::Render const & lhs, comp::Render const & rhs)
	{
		return lhs.zIndex < rhs.zIndex;
	});
}
