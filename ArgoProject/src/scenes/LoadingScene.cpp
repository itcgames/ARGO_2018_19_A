#include "stdafx.h"
#include "LoadingScene.h"
#include "factories/scenes/LoadingSceneFactory.h"
#include "components/AnimatedImage.h"

app::sce::LoadingScene::LoadingScene(SceneType & sceneManagerType)
	: BaseScene(sceneManagerType
		, util::make_vector<UpdateSystem>({
			UpdateSystem(std::in_place_type<app::sys::InputSystem>),
			UpdateSystem(std::in_place_type<app::sys::CommandSystem>),
			UpdateSystem(std::in_place_type<app::sys::CameraSystem>),
			UpdateSystem(std::in_place_type<app::sys::DebugSystem>, sceneManagerType),
			UpdateSystem(std::in_place_type<app::sys::LoadingSystem>),
			UpdateSystem(std::in_place_type<app::sys::DestroySystem>)
			})

		, util::make_vector<DrawSystem>({
			DrawSystem(std::in_place_type<app::sys::AnimatorSystem>),
			DrawSystem(std::in_place_type<app::sys::RenderSystem>)
			}))
{
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("LOADING SCENE Constructed");
	}
}

void app::sce::LoadingScene::start()
{
	auto sceneFactory = fact::sce::LoadingSceneFactory();
	auto entities = BaseScene::createEntities(sceneFactory);
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("SPLASH SCENE: Creating entities");
		for (auto const & entity : entities)
		{
			Console::writeLine({ "  Created entity[", std::to_string(entity), "]" });
		}
	}
}

void app::sce::LoadingScene::end()
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

void app::sce::LoadingScene::update(app::time::seconds const & dt)
{
	BaseScene::update(dt);
	if (m_resourceManager.isLoaded())
		m_sceneManagerType = SceneType::MainMenu;
}