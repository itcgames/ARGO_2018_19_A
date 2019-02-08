#include "stdafx.h"
#include "MultiplayerLevelScene.h"
#include "factories/scenes/MultiplayerLevelSceneFactory.h"

app::sce::MultiplayerLevelScene::MultiplayerLevelScene(SceneType & sceneManagerType)
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
		Console::writeLine("MULTIPLAYER LEVEL SCENE Constructed");
	}
}

void app::sce::MultiplayerLevelScene::start()
{
	auto const & entities = fact::sce::MultiplayerLevelSceneFactory().create();
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("MULTIPLAYER LEVEL SCENE: Creating entities");
		for (auto const & entity : entities)
		{
			Console::writeLine({ "  Created entity[", std::to_string(entity), "]" });
		}
	}
}

void app::sce::MultiplayerLevelScene::end()
{
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("MULTIPLAYER LEVEL SCENE: Destroying entities");
		m_registry.each([](app::Entity const entity)
		{
			Console::writeLine({ "  Destroyed entity[", std::to_string(entity), "]" });
		});
	}
	m_registry.reset();
}

