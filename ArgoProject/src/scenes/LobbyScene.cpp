#include "stdafx.h"
#include "LobbyScene.h"
#include "factories/scenes/LobbySceneFactory.h"

app::sce::LobbyScene::LobbyScene(SceneType & sceneManagerType)
	: BaseScene(sceneManagerType
		, util::make_vector<UpdateSystem>({
			UpdateSystem(std::in_place_type<app::sys::InputSystem>),
			UpdateSystem(std::in_place_type<app::sys::CommandSystem>),
			UpdateSystem(std::in_place_type<app::sys::MotionSystem>),
			UpdateSystem(std::in_place_type<app::sys::AirMotionSystem>),
			UpdateSystem(std::in_place_type<app::sys::DashSystem>),
			UpdateSystem(std::in_place_type<app::sys::StateMachineSystem>),
			UpdateSystem(std::in_place_type<app::sys::CameraSystem>),
			UpdateSystem(std::in_place_type<app::sys::NetworkSystem>, sceneManagerType),
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
		Console::writeLine("LOBBY SCENE Constructed");
	}
}

void app::sce::LobbyScene::start()
{
	auto sceneFactory = fact::sce::LobbySceneFactory();
	auto entities = BaseScene::createEntities(sceneFactory);
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("LOBBY SCENE: Creating entities");
		for (auto const & entity : entities)
		{
			Console::writeLine({ "  Created entity[", std::to_string(entity), "]" });
		}
	}
}

void app::sce::LobbyScene::end()
{
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("LOBBY SCENE: Destroying entities");
		m_registry.each([](app::Entity const entity)
		{
			Console::writeLine({ "  Destroyed entity[", std::to_string(entity), "]" });
		});
	}
	if (m_client.hasInit() && m_sceneManagerType != SceneType::LobbySelect && m_sceneManagerType != SceneType::MultiplayerLevel) { m_client.deinitNetwork(); }
}

