#include "stdafx.h"
#include "RenderTextSystem.h"
#include "singletons/WindowSingleton.h"

#include "components/Camera.h"
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Text.h"

app::sys::RenderTextSystem::RenderTextSystem()
	: m_window(app::sin::Window::get())
	, m_renderText()
	, m_view()
{
	m_registry.prepare<comp::Location, comp::Dimensions, comp::Text>();
}

void app::sys::RenderTextSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Camera>()
		.each([&, this](app::Entity const entity, comp::Camera const & camera)
	{
		m_view.position = camera.center;
		m_view.size = camera.size;
		m_window.setView(m_view);
		m_registry.view<comp::Location, comp::Dimensions, comp::Text>(entt::persistent_t())
			.each([&, this](app::Entity const entity, comp::Location const & location, comp::Dimensions const & dimensions, comp::Text const & text)
		{
			m_renderText.setPosition(location.position);
			m_renderText.setRotation(location.orientation);
			m_renderText.setSize(dimensions.size);
			m_renderText.setOrigin(dimensions.origin);
			m_renderText.setFont(text.font);
			m_renderText.setText(text.string);
			m_window.render(m_renderText);
		});
		m_window.resetView();
	});
}
