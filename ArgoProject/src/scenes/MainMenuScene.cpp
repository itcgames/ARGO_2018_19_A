#include "stdafx.h"
#include "MainMenuScene.h"
#include "factories/scenes/MainMenuSceneFactory.h"

app::sce::MainMenuScene::MainMenuScene(SceneType & sceneManagerType)
	: BaseScene(sceneManagerType
		, util::make_vector<UpdateSystem>({
			UpdateSystem(std::in_place_type<app::sys::InputSystem>),
			UpdateSystem(std::in_place_type<app::sys::CommandSystem>),
			UpdateSystem(std::in_place_type<app::sys::MotionSystem>),
			UpdateSystem(std::in_place_type<app::sys::AirMotionSystem>),
			UpdateSystem(std::in_place_type<app::sys::DashSystem>),
			UpdateSystem(std::in_place_type<app::sys::StateMachineSystem>),
			UpdateSystem(std::in_place_type<app::sys::CameraSystem>)
		})
		, util::make_vector<DrawSystem>({
			DrawSystem(std::in_place_type<app::sys::AnimatorSystem>),
			DrawSystem(std::in_place_type<app::sys::RenderSystem>)
		}))
{
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("SPLASH SCENE Constructed");
	}
}

app::sce::MainMenuScene::~MainMenuScene()
{
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("SPLASH SCENE Destructed");
	}
}

void app::sce::MainMenuScene::start()
{
	auto const & entities = fact::sce::MainMenuSceneFactory().create();
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("SPLASH SCENE: Creating entities");
		for (auto const & entity : entities)
		{
			Console::writeLine({ "  Created entity[", std::to_string(entity), "]" });
		}
	}
}

void app::sce::MainMenuScene::end()
{
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("SPLASH SCENE: Destroying entities");
		m_registry.each([](app::Entity const entity)
		{
			Console::writeLine({ "  Destroyed entity[", std::to_string(entity), "]" });
		});
	}
	m_registry.reset();
}

