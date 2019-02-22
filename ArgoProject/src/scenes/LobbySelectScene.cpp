#include "stdafx.h"
#include "LobbySelectScene.h"
#include "factories/scenes/LobbySelectSceneFactory.h"

app::sce::LobbySelectScene::LobbySelectScene(SceneType & sceneManagerType)
	: BaseScene(sceneManagerType
		, util::make_vector<UpdateSystem>({
			UpdateSystem(std::in_place_type<app::sys::InputSystem>),
			UpdateSystem(std::in_place_type<app::sys::ButtonSystem>),
			UpdateSystem(std::in_place_type<app::sys::WidgetNavigationSystem>),
			UpdateSystem(std::in_place_type<app::sys::CommandSystem>),
			UpdateSystem(std::in_place_type<app::sys::CameraSystem>),
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
		Console::writeLine("LOBBY SELECT SCENE Constructed");
	}
}

void app::sce::LobbySelectScene::start()
{
	auto const & entities = fact::sce::LobbySelectSceneFactory().create();
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("LOBBY SELECT SCENE: Creating entities");
		for (auto const & entity : entities)
		{
			Console::writeLine({ "  Created entity[", std::to_string(entity), "]" });
		}
	}
}

void app::sce::LobbySelectScene::end()
{
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("LOBBY SELECT SCENE: Destroying entities");
		m_registry.each([](app::Entity const entity)
		{
			Console::writeLine({ "  Destroyed entity[", std::to_string(entity), "]" });
		});
	}
	m_registry.reset();
}

