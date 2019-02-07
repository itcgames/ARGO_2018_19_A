#include "stdafx.h"
#include "TutorialLevelScene.h"
#include "factories/scenes/TutorialLevelSceneFactory.h"

app::sce::TutorialLevelScene::TutorialLevelScene(SceneType & sceneManagerType)
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

app::sce::TutorialLevelScene::~TutorialLevelScene()
{
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("SPLASH SCENE Destructed");
	}
}

void app::sce::TutorialLevelScene::start()
{
	auto const & entities = fact::sce::TutorialLevelSceneFactory().create();
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("SPLASH SCENE: Creating entities");
		for (auto const & entity : entities)
		{
			Console::writeLine({ "  Created entity[", std::to_string(entity), "]" });
		}
	}
}

void app::sce::TutorialLevelScene::end()
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

