#include "stdafx.h"
#include "CreditsScene.h"
#include "factories/scenes/CreditsSceneFactory.h"

app::sce::CreditsScene::CreditsScene(SceneType & sceneManagerType)
	: BaseScene(sceneManagerType
		, util::make_vector<UpdateSystem>({
			UpdateSystem(std::in_place_type<app::sys::InputSystem>),
			UpdateSystem(std::in_place_type<app::sys::CommandSystem>),
			UpdateSystem(std::in_place_type<app::sys::CameraSystem>),
			UpdateSystem(std::in_place_type<app::sys::DebugSystem>, sceneManagerType)
			})
		, util::make_vector<DrawSystem>({
			DrawSystem(std::in_place_type<app::sys::AnimatorSystem>),
			DrawSystem(std::in_place_type<app::sys::RenderSystem>)
			}))
{
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("CREDITS SCENE Constructed");
	}
}

void app::sce::CreditsScene::start()
{
	auto const & entities = fact::sce::CreditsSceneFactory().create();
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("CREDITS SCENE: Creating entities");
		for (auto const & entity : entities)
		{
			Console::writeLine({ "  Created entity[", std::to_string(entity), "]" });
		}
	}
}

void app::sce::CreditsScene::end()
{
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("CREDITS SCENE: Destroying entities");
		m_registry.each([](app::Entity const entity)
		{
			Console::writeLine({ "  Destroyed entity[", std::to_string(entity), "]" });
		});
	}
	m_registry.reset();
}

