#include "stdafx.h"
#include "SplashScene.h"
#include "factories/scenes/SplashSceneFactory.h"

app::sce::SplashScene::SplashScene()
	: BaseScene(SceneType::Splash
		, UpdateSystems{
			UpdateSystem(std::in_place_type<app::sys::InputSystem>),
			UpdateSystem(std::in_place_type<app::sys::CommandSystem>),
			UpdateSystem(std::in_place_type<app::sys::AirMotionSystem>),
			UpdateSystem(std::in_place_type<app::sys::StateMachineSystem>),
			UpdateSystem(std::in_place_type<app::sys::MotionSystem>),
			UpdateSystem(std::in_place_type<app::sys::CameraSystem>)
		}
		, DrawSystems{
			DrawSystem(std::in_place_type<app::sys::AnimatorSystem>),
			DrawSystem(std::in_place_type<app::sys::RenderSystem>)
		})
{
	auto const & entities = fact::sce::SplashSceneFactory().create();
	if constexpr (DEBUG_MODE)
	{
		for (auto const & entity : entities)
		{
			Console::writeLine({ "Created entity[", std::to_string(entity), "]" });
		}
	}
}
