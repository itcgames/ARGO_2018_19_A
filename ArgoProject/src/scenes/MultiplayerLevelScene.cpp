#include "stdafx.h"
#include "MultiplayerLevelScene.h"
#include "factories/scenes/MultiplayerLevelSceneFactory.h"
#include "components/Input.h"
#include "components/Goal.h"

app::sce::MultiplayerLevelScene::MultiplayerLevelScene(SceneType & sceneManagerType)
	: BaseScene(sceneManagerType
		, util::make_vector<UpdateSystem>({
			UpdateSystem(std::in_place_type<app::sys::InputSystem>),
			UpdateSystem(std::in_place_type<app::sys::CommandSystem>),
			UpdateSystem(std::in_place_type<app::sys::MotionSystem>),
			UpdateSystem(std::in_place_type<app::sys::AirMotionSystem>),
			UpdateSystem(std::in_place_type<app::sys::DashSystem>),
			UpdateSystem(std::in_place_type<app::sys::StateMachineSystem>),
			UpdateSystem(std::in_place_type<app::sys::CameraSystem>),
			UpdateSystem(std::in_place_type<app::sys::CurrentGroundSystem>),
			UpdateSystem(std::in_place_type<app::sys::FollowEntitySystem>),
			UpdateSystem(std::in_place_type<app::sys::CollisionSystem>),
			UpdateSystem(std::in_place_type<app::sys::HealthSystem>),
			UpdateSystem(std::in_place_type<app::sys::NetworkSystem>, sceneManagerType),
			UpdateSystem(std::in_place_type<app::sys::SendPlayerDataSystem>),
			UpdateSystem(std::in_place_type<app::sys::DebugSystem>, sceneManagerType),
			UpdateSystem(std::in_place_type<app::sys::DestroySystem>)
			})
		, util::make_vector<DrawSystem>({
			DrawSystem(std::in_place_type<app::sys::AnimatorSystem>),
			DrawSystem(std::in_place_type<app::sys::RenderSystem>)
			}))
	, m_entities()
	, m_resetSignal(false)
{
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("LEVEL SCENE Constructed");
	}
}

void app::sce::MultiplayerLevelScene::start()
{
	auto && entities = fact::sce::MultiplayerLevelSceneFactory().create();
	m_entities.insert(m_entities.end(), std::make_move_iterator(entities.begin()), std::make_move_iterator(entities.end()));
	m_registry.destruction<comp::Input>().connect<MultiplayerLevelScene, &MultiplayerLevelScene::onInputDestroyed>(this);
	m_registry.destruction<comp::Goal>().connect<MultiplayerLevelScene, &MultiplayerLevelScene::onGoalDestroyed>(this);
	m_completeSignal = false;
	m_resetSignal = false;
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("MULTIPLAYER LEVEL SCENE: Creating entities");
		for (auto const & entity : m_entities)
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
		for (auto const & entity : m_entities)
		{
			Console::writeLine({ "  Destroyed entity[", std::to_string(entity), "]" });
		}
	}
	m_registry.destruction<comp::Input>().disconnect<MultiplayerLevelScene, &MultiplayerLevelScene::onInputDestroyed>(this);
	m_registry.destruction<comp::Goal>().disconnect<MultiplayerLevelScene, &MultiplayerLevelScene::onGoalDestroyed>(this);
	m_registry.reset();
}

void app::sce::MultiplayerLevelScene::update(app::time::seconds const & dt)
{
	if (m_resetSignal)
	{
		this->reset();
		m_resetSignal = false;
	}
	if (m_completeSignal)
	{
		end();
		levelComplete();
	}
	app::sce::BaseScene::update(dt);
}

void app::sce::MultiplayerLevelScene::onInputDestroyed(app::Registry & registry, app::Entity inputEntity)
{
	m_resetSignal = true;
}

void app::sce::MultiplayerLevelScene::onGoalDestroyed(app::Registry & registry, app::Entity goalEntity)
{
	m_completeSignal = true;
}

void app::sce::MultiplayerLevelScene::reset()
{
	for (auto const & e : m_entities)
	{
		if (m_registry.valid(e)) { m_registry.destroy(e); }
	}
	m_completeSignal = false;
	m_entities.clear();
	auto && entities = fact::sce::MultiplayerLevelSceneFactory().create();
	m_entities.insert(m_entities.end(), std::make_move_iterator(entities.begin()), std::make_move_iterator(entities.end()));
}

void app::sce::MultiplayerLevelScene::levelComplete()
{
	m_sceneManagerType = (SceneType::MainMenu);
}