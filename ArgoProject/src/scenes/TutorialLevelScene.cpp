#include "stdafx.h"
#include "TutorialLevelScene.h"
#include "factories/scenes/TutorialLevelSceneFactory.h"
#include "components/Input.h"
#include "components/Goal.h"
#include "components/Layer.h"

app::sce::TutorialLevelScene::TutorialLevelScene(SceneType & sceneManagerType)
	: BaseScene(sceneManagerType
		, util::make_vector<UpdateSystem>({
			UpdateSystem(std::in_place_type<app::sys::InputSystem>),
			UpdateSystem(std::in_place_type<app::sys::CommandSystem>),
			UpdateSystem(std::in_place_type<app::sys::MotionSystem>),
			UpdateSystem(std::in_place_type<app::sys::AirMotionSystem>),
			UpdateSystem(std::in_place_type<app::sys::DashSystem>),
			UpdateSystem(std::in_place_type<app::sys::StateMachineSystem>),
			UpdateSystem(std::in_place_type<app::sys::CameraSystem>),
			UpdateSystem(std::in_place_type<app::sys::AISystem>),
			UpdateSystem(std::in_place_type<app::sys::CurrentGroundSystem>),
			UpdateSystem(std::in_place_type<app::sys::FollowEntitySystem>),
			UpdateSystem(std::in_place_type<app::sys::SeekEntitySystem>),
			UpdateSystem(std::in_place_type<app::sys::DiscReturnSystem>),
			UpdateSystem(std::in_place_type<app::sys::CollisionSystem>),
			UpdateSystem(std::in_place_type<app::sys::HealthSystem>),
			UpdateSystem(std::in_place_type<app::sys::BombExplosionSystem>),
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
		Console::writeLine("TUTORIAL LEVEL SCENE Constructed");
	}
}

void app::sce::TutorialLevelScene::start()
{
	auto sceneFactory = fact::sce::TutorialLevelSceneFactory();
	auto entities = BaseScene::createEntities(sceneFactory);
	m_entities.insert(m_entities.end(), std::make_move_iterator(entities.begin()), std::make_move_iterator(entities.end()));
	m_registry.destruction<comp::Input>().connect<TutorialLevelScene, &TutorialLevelScene::onInputDestroyed>(this);
	m_registry.destruction<comp::Goal>().connect<TutorialLevelScene, &TutorialLevelScene::onGoalDestroyed>(this);
	m_completeSignal = false;
	m_resetSignal = false;
	if constexpr (false)
	{
		Console::writeLine("TUTORIAL LEVEL SCENE: Creating entities");
		for (auto const & entity : m_entities)
		{
			Console::writeLine({ "  Created entity[", std::to_string(entity), "]" });
		}
	}
}

void app::sce::TutorialLevelScene::end()
{
	if constexpr (false)
	{
		Console::writeLine("TUTORIAL LEVEL SCENE: Destroying entities");
		for (auto const & entity : m_entities)
		{
			Console::writeLine({ "  Destroyed entity[", std::to_string(entity), "]" });
		}
	}
	m_registry.destruction<comp::Input>().disconnect<TutorialLevelScene, &TutorialLevelScene::onInputDestroyed>(this);
	m_registry.destruction<comp::Goal>().disconnect<TutorialLevelScene, &TutorialLevelScene::onGoalDestroyed>(this);
	m_registry.reset();
}

void app::sce::TutorialLevelScene::update(app::time::seconds const & dt)
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

void app::sce::TutorialLevelScene::onInputDestroyed(app::Registry & registry, app::Entity inputEntity)
{
	m_resetSignal = true;
}

void app::sce::TutorialLevelScene::onGoalDestroyed(app::Registry & registry, app::Entity goalEntity)
{
	m_completeSignal = true;
}

void app::sce::TutorialLevelScene::reset()
{
	for (auto const & e : m_entities)
	{
		if (m_registry.valid(e)) { m_registry.destroy(e); }
	}
	m_completeSignal = false;
	m_entities.clear();
	auto && entities = fact::sce::TutorialLevelSceneFactory().create();
	m_entities.insert(m_entities.end(), std::make_move_iterator(entities.begin()), std::make_move_iterator(entities.end()));
}

void app::sce::TutorialLevelScene::levelComplete()
{
	m_sceneManagerType = (SceneType::MainMenu);
}