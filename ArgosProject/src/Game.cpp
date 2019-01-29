#include "stdafx.h"
#include "Game.h"

app::Game::Game()
	: m_running(true)
	, m_keyHandler()
	, m_mouseHandler()
	, m_window(m_keyHandler, m_mouseHandler, "ARGOS Souls", 1366u, 768u)
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
	m_window.display();
}
