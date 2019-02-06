#include "stdafx.h"
#include "Game.h"
#include "singletons/ControllerHandlerSingleton.h"
#include "singletons/KeyHandlerSingleton.h"
#include "singletons/MouseHandlerSingleton.h"
#include "singletons/RegistrySingleton.h"
#include "singletons/WindowSingleton.h"

// components
#include "components/Camera.h"

// factories
#include "factories/PlayerFactory.h"
app::Game::Game()
	: m_running(true)
	, m_controllerHandler(app::sin::ControllerHandler::get())
	, m_keyHandler(app::sin::KeyHandler::get())
	, m_mouseHandler(app::sin::MouseHandler::get())
	, m_window(app::sin::Window::get())
	, m_registry(app::sin::Registry::get())

	, m_updateSystems{
		UpdateSystem(std::in_place_type<app::sys::InputSystem>),
		UpdateSystem(std::in_place_type<app::sys::CommandSystem>),
		UpdateSystem(std::in_place_type<app::sys::AirMotionSystem>),
		UpdateSystem(std::in_place_type<app::sys::StateMachineSystem>),
		UpdateSystem(std::in_place_type<app::sys::MotionSystem>),
		UpdateSystem(std::in_place_type<app::sys::CameraSystem>)
	}
	, m_drawSystems{
		DrawSystem(std::in_place_type<app::sys::AnimatorSystem>),
		DrawSystem(std::in_place_type<app::sys::RenderSystem>)
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
		auto playerEntity = fact::PlayerFactory(m_window.getRenderer()).create();
		this->createCamera(playerEntity);
		return true;
	}
	catch (const std::exception&)
	{
		Console::writeLine({ "ERROR: " });
		return false;
	}
}

app::Entity app::Game::createCamera(std::optional<app::Entity> target)
{
	app::Entity const entity = m_registry.create();

	auto camera = comp::Camera();
	camera.position = {  };
	camera.size = { 1366.0f, 768.0f };
	camera.target = target;
	m_registry.assign<decltype(camera)>(entity, std::move(camera));

	return entity;
}
