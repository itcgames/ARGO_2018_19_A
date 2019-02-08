#include "stdafx.h"
#include "CharacterSelectScene.h"
#include "factories/scenes/CharacterSelectSceneFactory.h"

app::sce::CharacterSelectScene::CharacterSelectScene(SceneType & sceneManagerType)
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
		Console::writeLine("CHARACTER SELECT SCENE Constructed");
	}
}

void app::sce::CharacterSelectScene::start()
{
	auto const & entities = fact::sce::CharacterSelectSceneFactory().create();
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("CHARACTER SELECT SCENE: Creating entities");
		for (auto const & entity : entities)
		{
			Console::writeLine({ "  Created entity[", std::to_string(entity), "]" });
		}
	}
}

void app::sce::CharacterSelectScene::end()
{
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("CHARACTER SELECT SCENE: Destroying entities");
		m_registry.each([](app::Entity const entity)
		{
			Console::writeLine({ "  Destroyed entity[", std::to_string(entity), "]" });
		});
	}
	m_registry.reset();
}

