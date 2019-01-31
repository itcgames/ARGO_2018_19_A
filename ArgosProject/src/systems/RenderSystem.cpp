#include "stdafx.h"
#include "RenderSystem.h"

app::sys::RenderSystem::RenderSystem(app::gra::Window & window)
	: BaseSystem()
	, m_window(window)
{
}

void app::sys::RenderSystem::update(app::time::seconds const & dt)
{
	auto rect = app::gra::RenderRect();
	rect.setPosition({ 600.0, 300.0 });
	rect.setTexture(app::gra::Texture(m_window.getRenderer(), "./res/image.png"));
	rect.setSize({ 400.0, 400.0 });
	rect.setOrigin(rect.getSize() / 2.0);
	rect.setRotation(45.0);
	m_window.draw(rect);
}
