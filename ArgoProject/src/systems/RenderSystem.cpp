#include "stdafx.h"
#include "RenderSystem.h"

// components
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Render.h"
#include "components/Camera.h"

app::sys::RenderSystem::RenderSystem(app::gra::Window & window)
	: BaseSystem()
	, m_window(window)
{
}

void app::sys::RenderSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Camera>()
		.each([&, this](app::Entity const camEntity, comp::Camera & camera)
	{
		m_view.position = camera.position;
		m_view.size = camera.size;
		m_window.setView(m_view);
		m_registry.view<comp::Location, comp::Dimensions, comp::Render>()
			.each([&, this](app::Entity const entity, comp::Location & location, comp::Dimensions & dimensions, comp::Render & render)
		{
			m_renderRect.setPosition(location.position);
			m_renderRect.setRotation(location.orientation);
			m_renderRect.setSize(dimensions.size);
			m_renderRect.setOrigin(dimensions.origin);
			m_renderRect.setTexture(render.texture);
			m_renderRect.setSourceRect(render.source);
			m_window.draw(m_renderRect);
		});
		m_window.resetView();
	});
}
