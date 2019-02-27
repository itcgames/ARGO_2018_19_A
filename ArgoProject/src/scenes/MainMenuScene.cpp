#include "stdafx.h"
#include "MainMenuScene.h"
#include "factories/scenes/MainMenuSceneFactory.h"
#include "factories/entities/LevelDemoFactory.h"
#include "components/Destroy.h"
#include "components/AI.h"
#include "components/Background.h"

app::sce::MainMenuScene::MainMenuScene(SceneType & sceneManagerType)
	: BaseScene(sceneManagerType
		, util::make_vector<UpdateSystem>({
			UpdateSystem(std::in_place_type<app::sys::InputSystem>),
			UpdateSystem(std::in_place_type<app::sys::ButtonSystem>),
			UpdateSystem(std::in_place_type<app::sys::WidgetNavigationSystem>),
			UpdateSystem(std::in_place_type<app::sys::CommandSystem>),
			UpdateSystem(std::in_place_type<app::sys::MotionSystem>),
			UpdateSystem(std::in_place_type<app::sys::AirMotionSystem>),
			UpdateSystem(std::in_place_type<app::sys::DashSystem>),
			UpdateSystem(std::in_place_type<app::sys::StateMachineSystem>),
			UpdateSystem(std::in_place_type<app::sys::CameraSystem>),
			UpdateSystem(std::in_place_type<app::sys::HealthSystem>),
			UpdateSystem(std::in_place_type<app::sys::AISystem>),
			UpdateSystem(std::in_place_type<app::sys::CurrentGroundSystem>),
			UpdateSystem(std::in_place_type<app::sys::CollisionSystem>),
			UpdateSystem(std::in_place_type<app::sys::NetworkSystem>),
			UpdateSystem(std::in_place_type<app::sys::DebugSystem>, sceneManagerType),
			UpdateSystem(std::in_place_type<app::sys::DestroySystem>)
			})
		, util::make_vector<DrawSystem>({
			DrawSystem(std::in_place_type<app::sys::AnimatorSystem>),
			DrawSystem(std::in_place_type<app::sys::RenderSystem>)
			}))
{
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("MAIN MENU SCENE Constructed");
	}
}

void app::sce::MainMenuScene::start()
{
	auto const & entities = fact::sce::MainMenuSceneFactory(m_sceneManagerType, m_demoFactory).create();
	m_registry.destruction<comp::Background>().connect<MainMenuScene, &MainMenuScene::startDemo>(this);
	m_registry.destruction<comp::AI>().connect<MainMenuScene, &MainMenuScene::reset>(this);
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("MAIN MENU SCENE: Creating entities");
		for (auto const & entity : entities)
		{
			Console::writeLine({ "  Created entity[", std::to_string(entity), "]" });
		}
	}
}

void app::sce::MainMenuScene::end()
{
	m_registry.destruction<comp::Background>().disconnect<MainMenuScene, &MainMenuScene::startDemo>(this);
	m_registry.destruction<comp::AI>().disconnect<MainMenuScene, &MainMenuScene::reset>(this);
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("MAIN MENU SCENE: Destroying entities");
		m_registry.each([this](app::Entity const entity)
		{
			Console::writeLine({ "  Destroyed entity[", std::to_string(entity), "]" });
			m_registry.destroy(entity);
		});
	}
}

void app::sce::MainMenuScene::startDemo(app::Registry & registry, app::Entity inputEntity)
{
	if (!m_demoFactory.has_value()) { throw std::exception("Demo factory must be initialized"); }
	m_demoEntities = m_demoFactory->create();
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("MAIN MENU SCENE: Creating entities");
		for (auto const & entity : m_demoEntities)
		{
			Console::writeLine({ "  Created entity[", std::to_string(entity), "]" });
		}
	}
}

void app::sce::MainMenuScene::reset(app::Registry & registry, app::Entity inputEntity)
{
	if (resetDemo)
	{
		resetDemo = false;
		for (auto const & e : m_demoEntities)
		{
			if (m_registry.valid(e)) { m_registry.assign<comp::Destroy>(e); }
		}
		m_demoEntities.clear();
	}
	resetDemo = true;
	startDemo(m_registry, 1);
}