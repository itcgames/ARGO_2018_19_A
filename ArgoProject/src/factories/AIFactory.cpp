#include "stdafx.h"
#include "AIFactory.h"

#include "factories/NodeFactory.h"

// components
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/AirMotion.h"
#include "components/Animator.h"
#include "components/Layer.h"
#include "components/Render.h"
#include "components/Input.h"
#include "components/Commandable.h"
#include "components/Collision.h"
#include "components/PlatformDrop.h"
#include "components/CurrentGround.h"
#include "components/AI.h"
#include "components/Dashable.h"
#include "components/DoubleJump.h"
#include "commands/MoveCommand.h"
#include "commands/JumpCommand.h"
#include "commands/DashCommand.h"
#include "commands/FaceLeftCommand.h"
#include "commands/FaceRightCommand.h"
#include "commands/DropCommand.h"
#include "components/StateMachine.h"
#include "components/Health.h"

#include "fsm/AnimationStateMachine.h"
#include "fsm/states/AiWalkingAnimationState.h"

app::fact::AIFactory::AIFactory(math::Vector2f const & pos, math::Vector2f const & size)
	: m_position(pos), m_size(size)
{
}

std::vector<app::Entity> app::fact::AIFactory::create()
{
	auto entities = std::vector<app::Entity>();
	app::Entity const entity = m_entityFactory.create();

	auto location = comp::Location();
	location.position = m_position;
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = m_size;
	dimensions.origin = dimensions.size / 2.0f;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

	auto motion = comp::AirMotion();
	motion.speed = 0.0f;
	motion.direction = 0.0f;
	motion.angularSpeed = 0.0f;
	m_registry.assign<decltype(motion)>(entity, std::move(motion));

	auto animator = comp::Animator();
	m_registry.assign<decltype(animator)>(entity, std::move(animator));

	auto layer = comp::Layer();
	layer.zIndex = 90u;
	m_registry.assign<decltype(layer)>(entity, std::move(layer));

	auto render = comp::Render();
	m_registry.assign<decltype(render)>(entity, std::move(render));

	auto input = comp::Input();
	input.isRight = true;
	m_registry.assign<decltype(input)>(entity, std::move(input));

	auto doubleJump = comp::DoubleJump();
	doubleJump.canDoubleJump = true;
	m_registry.assign<decltype(doubleJump)>(entity, std::move(doubleJump));

	auto dashable = comp::Dashable();
	dashable.canDash = true;
	m_registry.assign<decltype(dashable)>(entity, std::move(dashable));

	auto commandable = comp::Commandable();
	m_registry.assign<decltype(commandable)>(entity, std::move(commandable));

	// Make sure render and animator components are already assigned before assigning a finite state machine.
	auto stateMachine = comp::StateMachine();
	stateMachine.instance = std::make_unique<fsm::AnimationStateMachine>();
	stateMachine.instance->setState(std::make_shared<fsm::sta::AiWalkingAnimationState>(entity));
	m_registry.assign<decltype(stateMachine)>(entity, std::move(stateMachine));

	auto collision = comp::Collision();
	collision.bounds = cute::c2AABB();
	m_registry.assign<decltype(collision)>(entity, std::move(collision));

	auto health = comp::Health();
	health.health = 1;
	m_registry.assign<decltype(health)>(entity, std::move(health));

	auto player = comp::PlatformDrop();
	m_registry.assign<decltype(player)>(entity, std::move(player));

	auto ground = comp::CurrentGround();
	m_registry.assign<decltype(ground)>(entity, std::move(ground));

	auto ai = comp::AI();

	auto loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
		std::make_shared<cmnd::MoveCommand>(entity, 0.0f, 20.0f)
	};
	auto initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
		std::make_shared<cmnd::JumpCommand>(entity, 400.0f)
	};
	auto node = app::fact::NodeFactory(math::Vector2f(750.0f, 200.0f), loopCmnds, initialCmnds).create();
	entities.push_back(node);

	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
		std::make_shared<cmnd::MoveCommand>(entity, 180.0f, 20.0f)
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
		
	};
	node = app::fact::NodeFactory(math::Vector2f(950.0f, 200.0f), loopCmnds, initialCmnds).create();
	entities.push_back(node);

	m_registry.assign<decltype(ai)>(entity, std::move(ai));

	entities.push_back(entity);

	return entities;
}
