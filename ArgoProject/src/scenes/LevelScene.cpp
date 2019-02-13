#include "stdafx.h"
#include "LevelScene.h"
#include "factories/scenes/LevelSceneFactory.h"
#include "components/Input.h"

app::sce::LevelScene::LevelScene(SceneType & sceneManagerType)
	: BaseScene(sceneManagerType
		, util::make_vector<UpdateSystem>({
			UpdateSystem(std::in_place_type<app::sys::InputSystem>),
			UpdateSystem(std::in_place_type<app::sys::CommandSystem>),
			UpdateSystem(std::in_place_type<app::sys::MotionSystem>),
			UpdateSystem(std::in_place_type<app::sys::AirMotionSystem>),
			UpdateSystem(std::in_place_type<app::sys::DashSystem>),
			UpdateSystem(std::in_place_type<app::sys::StateMachineSystem>),
			UpdateSystem(std::in_place_type<app::sys::CameraSystem>),
			UpdateSystem(std::in_place_type<app::sys::CollisionSystem>),
			UpdateSystem(std::in_place_type<app::sys::HealthSystem>),
			UpdateSystem(std::in_place_type<app::sys::CurrentGroundSystem>)
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

void app::sce::LevelScene::start()
{
	auto && entities = fact::sce::LevelSceneFactory().create();
	m_entities.insert(m_entities.end(), std::make_move_iterator(entities.begin()), std::make_move_iterator(entities.end()));
	m_registry.destruction<comp::Input>().connect<LevelScene, &LevelScene::onInputDestroyed>(this);
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("LEVEL SCENE: Creating entities");
		for (auto const & entity : m_entities)
		{
			Console::writeLine({ "  Created entity[", std::to_string(entity), "]" });
		}
	}
}

void app::sce::LevelScene::end()
{
	if constexpr (DEBUG_MODE)
	{
		Console::writeLine("LEVEL SCENE: Destroying entities");
		for (auto const & entity : m_entities)
		{
			Console::writeLine({ "  Destroyed entity[", std::to_string(entity), "]" });
		}
	}
	m_registry.destruction<comp::Input>().disconnect<LevelScene, &LevelScene::onInputDestroyed>(this);
	m_registry.reset();
}

void app::sce::LevelScene::update(app::time::seconds const & dt)
{
	if (m_resetSignal)
	{
		m_resetSignal = false;
		this->reset();
	}
	app::sce::BaseScene::update(dt);
}

void app::sce::LevelScene::onInputDestroyed(app::Registry & registry, app::Entity inputEntity)
{
	m_resetSignal = true;
}

void app::sce::LevelScene::reset()
{
	for (auto const & e : m_entities)
	{
		if (m_registry.valid(e)) { m_registry.destroy(e); }
	}
	m_entities.clear();
	auto && entities = fact::sce::LevelSceneFactory().create();
	m_entities.insert(m_entities.end(), std::make_move_iterator(entities.begin()), std::make_move_iterator(entities.end()));
}
