#include "stdafx.h"
#include "Game.h"

#include "graphics/Texture.h"

app::Game::Game()
	: m_running(true)
	, m_keyHandler()
	, m_mouseHandler()
	, m_window(m_keyHandler, m_mouseHandler, gra::WindowParameters{ "ARGOS Souls", 1366u, 768u })
{
}

app::Game::~Game()
{
	SDL_Quit();
}

void app::Game::pollEvents()
{
	m_window.pollEvents();
}

void app::Game::update(app::time::seconds const & dt)
{
}

void app::Game::render(app::time::seconds const & dt)
{
	m_window.clear();
	auto rect = app::gra::RenderRect();
	rect.setPosition({ 600.0, 300.0 });
	rect.setTexture(app::gra::Texture(m_window.getRenderer(), "./res/image.png"));
	rect.setSize({ 400.0, 400.0 });
	rect.setOrigin(rect.getSize() / 2.0);
	rect.setRotation(45.0);
	m_window.draw(rect);
	m_window.display();
}
