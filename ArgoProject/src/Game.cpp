#include "stdafx.h"
#include "Game.h"
#include "Registry.h"

// components
#include "components/Camera.h"

// factories
#include "factories/PlayerFactory.h"

app::Game::Game()
	: m_running(true)
	, m_controllerHandler()
	, m_keyHandler()
	, m_mouseHandler()
	, m_window(m_keyHandler, m_mouseHandler, m_controllerHandler, gra::WindowParameters{ "ARGO Souls", 1366u, 768u })
	, m_registry(app::Reg::get())

	, m_updateSystems{
		UpdateSystem(std::in_place_type<app::sys::MotionSystem>)
	}
	, m_drawSystems{
		DrawSystem(std::in_place_type<app::sys::AnimatorSystem>),
		DrawSystem(std::in_place_type<app::sys::RenderSystem>, m_window)
	}
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != NULL)
	{
		Console::writeLine({ "ERROR: SDL Failed to initialize [", SDL_GetError(), "]" });
		m_running = false;
	}
	m_running = m_running ? this->initEntities() : false;
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
	for (auto & variantSystem : m_updateSystems) { std::visit([&dt](auto & system) { system.update(dt); }, variantSystem); }
	m_controllerHandler.update();
	m_keyHandler.update();
	m_mouseHandler.update();
}

void app::Game::render(app::time::seconds const & dt)
{
	m_window.clear();
	for (auto & variantSystem : m_drawSystems) { std::visit([&dt](auto & system) { system.update(dt); }, variantSystem); }
	m_window.display();
}

bool app::Game::initEntities()
{
	try
	{
		this->createCamera();
		fact::PlayerFactory(m_window.getRenderer()).create();
		return true;
	}
	catch (const std::exception&)
	{
		Console::writeLine({ "ERROR: " });
		return false;
	}
}

app::Entity app::Game::createCamera()
{
	app::Entity const entity = m_registry.create();

	auto camera = comp::Camera();
	camera.position = { 250.0f, 50.0f };
	camera.size = { 1366.0f, 768.0f };
	m_registry.assign<decltype(camera)>(entity, std::move(camera));

	return entity;
}
