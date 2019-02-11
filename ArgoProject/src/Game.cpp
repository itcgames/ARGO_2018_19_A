#include "stdafx.h"
#include "Game.h"
#include "singletons/ControllerHandlerSingleton.h"
#include "singletons/KeyHandlerSingleton.h"
#include "singletons/MouseHandlerSingleton.h"
#include "singletons/RegistrySingleton.h"
#include "singletons/WindowSingleton.h"


app::Game::Game()
	: m_running(true)
	, m_controllerHandler(app::sin::ControllerHandler::get())
	, m_keyHandler(app::sin::KeyHandler::get())
	, m_mouseHandler(app::sin::MouseHandler::get())
	, m_window(app::sin::Window::get())
	, m_registry(app::sin::Registry::get())
	, m_sceneManager()
	, m_resourceManager()
	, m_syncResourceManager()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != NULL)
	{
		Console::writeLine({ "ERROR: SDL Failed to initialize [", SDL_GetError(), "]" });
		m_running = false;
	}
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
	m_sceneManager.update(dt);
	m_controllerHandler.update();
	m_keyHandler.update();
	m_mouseHandler.update();
}

void app::Game::render(app::time::seconds const & dt)
{
	m_window.clear();
	m_sceneManager.render(dt);
	m_window.display();
}
