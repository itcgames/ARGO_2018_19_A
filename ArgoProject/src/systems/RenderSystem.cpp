#include "stdafx.h"
#include "RenderSystem.h"

// components
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Render.h"

app::sys::RenderSystem::RenderSystem(app::gra::Window const & window)
	: BaseSystem()
	, m_window(window)
{
}

void app::sys::RenderSystem::update(app::time::seconds const & dt)
{
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
}
