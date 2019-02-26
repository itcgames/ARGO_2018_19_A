﻿#include "stdafx.h"
#include "MainMenuScene.h"
#include "factories/scenes/MainMenuSceneFactory.h"
#include "singletons/ClientSingleton.h"

app::sce::MainMenuScene::MainMenuScene(SceneType & sceneManagerType)
	: BaseScene(sceneManagerType
		, util::make_vector<UpdateSystem>({
			UpdateSystem(std::in_place_type<app::sys::InputSystem>),
			UpdateSystem(std::in_place_type<app::sys::ButtonSystem>),
			UpdateSystem(std::in_place_type<app::sys::WidgetNavigationSystem>),
			UpdateSystem(std::in_place_type<app::sys::CommandSystem>),
			UpdateSystem(std::in_place_type<app::sys::CameraSystem>),
			UpdateSystem(std::in_place_type<app::sys::NetworkSystem>, sceneManagerType),
			UpdateSystem(std::in_place_type<app::sys::DebugSystem>, sceneManagerType),
			UpdateSystem(std::in_place_type<app::sys::DestroySystem>)
			})
		, util::make_vector<DrawSystem>({
			DrawSystem(std::in_place_type<app::sys::AnimatorSystem>),
			DrawSystem(std::in_place_type<app::sys::RenderSystem>)
			}))
	, m_client(app::sin::Client::get())
{
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("MAIN MENU SCENE Constructed");
	}
}

void app::sce::MainMenuScene::start()
{
	auto const & entities = fact::sce::MainMenuSceneFactory(m_sceneManagerType).create();
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("MAIN MENU SCENE: Creating entities");
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
		Console::writeLine("MAIN MENU SCENE: Destroying entities");
		m_registry.each([this](app::Entity const entity)
		{
			Console::writeLine({ "  Destroyed entity[", std::to_string(entity), "]" });
		});
	}
	if (m_client.hasInit() && m_sceneManagerType != SceneType::LobbySelect) { m_client.deinitNetwork(); }
	m_registry.reset();
}

