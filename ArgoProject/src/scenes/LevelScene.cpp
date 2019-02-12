#include "stdafx.h"
#include "LevelScene.h"
#include "factories/scenes/LevelSceneFactory.h"

app::sce::LevelScene::LevelScene(SceneType & sceneManagerType)
	: BaseScene(sceneManagerType
		, util::make_vector<UpdateSystem>({
			UpdateSystem(std::in_place_type<app::sys::InputSystem>),
			UpdateSystem(std::in_place_type<app::sys::CommandSystem>),
			UpdateSystem(std::in_place_type<app::sys::MotionSystem>),
			UpdateSystem(std::in_place_type<app::sys::AirMotionSystem>),
			UpdateSystem(std::in_place_type<app::sys::DashSystem>),
			UpdateSystem(std::in_place_type<app::sys::StateMachineSystem>),
			UpdateSystem(std::in_place_type<app::sys::CollisionSystem>),
			UpdateSystem(std::in_place_type<app::sys::CameraSystem>)
		})
		, util::make_vector<DrawSystem>({
			DrawSystem(std::in_place_type<app::sys::AnimatorSystem>),
			DrawSystem(std::in_place_type<app::sys::RenderSystem>)
		}))
{
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("LEVEL SCENE Constructed");
	}
}

void app::sce::LevelScene::start()
{
	auto const & entities = fact::sce::LevelSceneFactory().create();
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("LEVEL SCENE: Creating entities");
		for (auto const & entity : entities)
		{
			Console::writeLine({ "  Created entity[", std::to_string(entity), "]" });
		}
	}
}

void app::sce::LevelScene::end()
{
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("LEVEL SCENE: Destroying entities");
		m_registry.each([](app::Entity const entity)
		{
			Console::writeLine({ "  Destroyed entity[", std::to_string(entity), "]" });
		});
	}
	m_registry.reset();
}

