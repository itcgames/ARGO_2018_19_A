#include "stdafx.h"
#include "LevelSelectScene.h"
#include "factories/scenes/LevelSelectSceneFactory.h"

app::sce::LevelSelectScene::LevelSelectScene(SceneType & sceneManagerType)
	: BaseScene(sceneManagerType
		, util::make_vector<UpdateSystem>({
			UpdateSystem(std::in_place_type<app::sys::InputSystem>),
			UpdateSystem(std::in_place_type<app::sys::CommandSystem>),
			UpdateSystem(std::in_place_type<app::sys::CameraSystem>)
			})
		, util::make_vector<DrawSystem>({
			DrawSystem(std::in_place_type<app::sys::AnimatorSystem>),
			DrawSystem(std::in_place_type<app::sys::RenderSystem>)
			}))
{
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("LEVEL SELECT SCENE Constructed");
	}
}

void app::sce::LevelSelectScene::start()
{
	auto const & entities = fact::sce::LevelSelectSceneFactory().create();
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("LEVEL SELECT SCENE: Creating entities");
		for (auto const & entity : entities)
		{
			Console::writeLine({ "  Created entity[", std::to_string(entity), "]" });
		}
	}
}

void app::sce::LevelSelectScene::end()
{
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("LEVEL SELECT SCENE: Destroying entities");
		m_registry.each([](app::Entity const entity)
		{
			Console::writeLine({ "  Destroyed entity[", std::to_string(entity), "]" });
		});
	}
	m_registry.reset();
}

