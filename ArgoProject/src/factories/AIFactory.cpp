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
#include "commands/AttackCommand.h"
#include "components/StateMachine.h"
#include "components/Health.h"
#include "components/CharacterType.h"
#include "components/Facing.h"

#include "fsm/AnimationStateMachine.h"
#include "fsm/states/AxeRunAnimationState.h"

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
	stateMachine.instance->setState(std::make_shared<fsm::sta::AxeRunAnimationState>(entity));
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

	auto characterType = comp::CharacterType();
	characterType.type = comp::CharacterType::Type::AXE;
	m_registry.assign<decltype(characterType)>(entity, std::move(characterType));

	auto facing = comp::Facing();
	facing.isRight = true;
	m_registry.assign<decltype(facing)>(entity, std::move(facing));

	float timeToLoopCommands = 0.75f;
	//auto rng = app::util::Random::gen(1, 3);
	auto rng = app::util::Random::gen(1,3);
	auto moveLeftCmnd = std::make_shared<cmnd::MoveCommand>(entity, -180.0f, 20.0f);
	auto moveRightCmnd = std::make_shared<cmnd::MoveCommand>(entity, 0.0f, 20.0f);
	auto jumpCmnd = std::make_shared<cmnd::JumpCommand>(entity, 400.0f);
	//fuzzification when hitting a node do one of a few commands and see how the ai responds
	//1
	//run command until it hits a new node
	auto loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{};
	auto initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{};
	if (rng == 1)
	{
		loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			moveRightCmnd
		};
		//run the command once 
		initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
		};
	}
	else if (rng == 2)
	{
		loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			moveRightCmnd
		};
		//run the command once 
		initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			jumpCmnd
		};	
	}
	else if (rng == 3)
	{
		loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			moveLeftCmnd
		};
		//run the command once 
		initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			jumpCmnd
		};
	}

	auto node = app::fact::NodeFactory(math::Vector2f(750.0f, 200.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//2
	timeToLoopCommands = 0.15f;
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
		moveRightCmnd
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			jumpCmnd 
	};
	node = app::fact::NodeFactory(math::Vector2f(950.0f, 200.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//3
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			jumpCmnd
	};
	node = app::fact::NodeFactory(math::Vector2f(1250.0f, 400.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//4
	timeToLoopCommands = 0.45f;
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			moveRightCmnd
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
	};
	node = app::fact::NodeFactory(math::Vector2f(1500.0f, 500.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//5
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			jumpCmnd
	};
	node = app::fact::NodeFactory(math::Vector2f(1700.0f, 450.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//6 
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			jumpCmnd
	};
	node = app::fact::NodeFactory(math::Vector2f(1750.0f, 400.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//7
	timeToLoopCommands = 0.5f;
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			moveRightCmnd
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
	};
	node = app::fact::NodeFactory(math::Vector2f(1820.0f, 250.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//8
	timeToLoopCommands = 0.3f;
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			moveRightCmnd
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			jumpCmnd
	};
	node = app::fact::NodeFactory(math::Vector2f(1970.0f, 250.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//9
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
					jumpCmnd
	};
	node = app::fact::NodeFactory(math::Vector2f(2200.0f, 150.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//10
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			jumpCmnd
	};
	node = app::fact::NodeFactory(math::Vector2f(2500.0f, 0.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//11
	timeToLoopCommands = 0.7f;
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			moveRightCmnd
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
	};
	node = app::fact::NodeFactory(math::Vector2f(2600.0f, -50.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//12
	timeToLoopCommands = 0.7f;
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			std::make_shared<cmnd::DropCommand>(entity)
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
	};
	node = app::fact::NodeFactory(math::Vector2f(2900.0f, -50.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//12.5 NODE TO BE DYNAMICALLY CREATED (DESTROY)
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			moveLeftCmnd
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			std::make_shared<cmnd::MoveCommand>(entity, 180.0f, 20.0f),
			std::make_shared<cmnd::DashCommand>(entity)
	};
	node = app::fact::NodeFactory(math::Vector2f(2900.0f, 200.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//13
	timeToLoopCommands = 0.4f;
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
		moveLeftCmnd
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
	};
	node = app::fact::NodeFactory(math::Vector2f(2650.0f, 650.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//14
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
		moveRightCmnd
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			std::make_shared<cmnd::DashCommand>(entity)
	};
	node = app::fact::NodeFactory(math::Vector2f(2500.0f, 880.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//15
	timeToLoopCommands = 4.5f;
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
		moveRightCmnd
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			std::make_shared<cmnd::DashCommand>(entity)
	};
	node = app::fact::NodeFactory(math::Vector2f(2800.0f, 880.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//16
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			jumpCmnd
	};
	node = app::fact::NodeFactory(math::Vector2f(4150.0f, 900.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//17
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			jumpCmnd
	};
	node = app::fact::NodeFactory(math::Vector2f(4150.0f, 770.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//18
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			moveLeftCmnd
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
	};
	node = app::fact::NodeFactory(math::Vector2f(4150.0f, 650.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//19
	timeToLoopCommands = 2.0f;
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			moveLeftCmnd
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			jumpCmnd
	};
	node = app::fact::NodeFactory(math::Vector2f(4000.0f, 680.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//20
	timeToLoopCommands = 2.0f;
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			moveLeftCmnd
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			jumpCmnd
	};
	node = app::fact::NodeFactory(math::Vector2f(3500.0f, 700.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//21
	timeToLoopCommands = 2.0f;
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			moveRightCmnd
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
	};
	node = app::fact::NodeFactory(math::Vector2f(3000.0f, 650.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//22
	timeToLoopCommands = 2.0f;
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			moveRightCmnd
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			jumpCmnd
	};
	node = app::fact::NodeFactory(math::Vector2f(3120.0f, 665.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//23
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			jumpCmnd
	};
	node = app::fact::NodeFactory(math::Vector2f(3250.0f, 450.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//24
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			moveRightCmnd
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			jumpCmnd
	};
	node = app::fact::NodeFactory(math::Vector2f(3600.0f, 380.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//25
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			moveRightCmnd
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			jumpCmnd
	};
	node = app::fact::NodeFactory(math::Vector2f(3850.0f, 300.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//26
	timeToLoopCommands = 0.8f;
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			moveLeftCmnd
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
	};
	node = app::fact::NodeFactory(math::Vector2f(4200.0f, 250.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//27
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			moveLeftCmnd
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			jumpCmnd
	};
	node = app::fact::NodeFactory(math::Vector2f(4050.0f, 290.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);

	//28
	loopCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			moveLeftCmnd
	};
	initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
			jumpCmnd
	};
	node = app::fact::NodeFactory(math::Vector2f(3850.0f, 100.0f), loopCmnds, initialCmnds, timeToLoopCommands).create();
	entities.push_back(node);


	m_registry.assign<decltype(ai)>(entity, std::move(ai));

	entities.push_back(entity);

	return entities;
}
