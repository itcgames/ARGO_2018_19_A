#include "stdafx.h"
#include "AIFactory.h"

#include "factories/NodeFactory.h"

// components
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/AirMotion.h"
#include "components/Animator.h"
#include "components/Render.h"
#include "components/Input.h"
#include "components/Commandable.h"
#include "components/Collision.h"
#include "components/PlatformDrop.h"
#include "components/CurrentGround.h"
#include "components/AI.h"

#include "commands/MoveCommand.h"
#include "commands/JumpCommand.h"
#include "commands/DashCommand.h"
#include "commands/FaceLeftCommand.h"
#include "commands/FaceRightCommand.h"
#include "commands/DropCommand.h"
#include "components/StateMachine.h"
#include "components/Health.h"

app::fact::AIFactory::AIFactory(math::Vector2f pos, math::Vector2f size)
	: m_position(pos), m_size(size)
{
}

app::Entity const app::fact::AIFactory::create()
{
	app::Entity const entity = EntityFactory::create();

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
	animator.loop = true; // tell animator to loop animation when it reaches the end.
	animator.time = 0.0f; // Separate time tracking for the animation, leave it at zero
	animator.currentFrame = math::Vector2i{ 0, 0 }; // Starting frame
	animator.position = { 0, 0 }; // Starting position
	animator.frameSize = math::Vector2i{ 200, 150 }; // width,height of each frame
	animator.numOfFrames = math::Vector2i{ 3, 0 }; // number of frames in the X axis and Y axis
	// time it takes to switch from one frame to another.
	// calculating it by taking full_duration / (number of total frames)
	// while dealing with edge case of any of the frames being zero
	animator.perFrame = 90.0f / (std::max(animator.numOfFrames.x, 1) * std::max(animator.numOfFrames.y, 1));
	m_registry.assign<decltype(animator)>(entity, std::move(animator));

	auto render = comp::Render();
	render.texture = m_resourceManager.getTexture(app::res::TextureKey::DebugAnimation);
	m_registry.assign<decltype(render)>(entity, std::move(render));

	//auto input = comp::Input();
	//input.m_isRight = true;
	//input.m_canDoubleJump = true;
	//input.m_canDash = true;
	//m_registry.assign<decltype(input)>(entity, std::move(input));

	auto commandable = comp::Commandable();
	m_registry.assign<decltype(commandable)>(entity, std::move(commandable));

	auto stateMachine = comp::StateMachine();
	stateMachine.instance = nullptr;
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
		std::make_shared<cmnd::MoveCommand>(entity, 0, 20)
	};
	auto initialCmnds = std::list<std::shared_ptr<cmnd::BaseCommand>>{
		std::make_shared<cmnd::JumpCommand>(entity, 400.0f)
	};
	auto startNode = app::fact::NodeFactory(math::Vector2f(875, 450), loopCmnds, initialCmnds).create();
	m_nodes.push_back(startNode);

	ai.m_currentNode = startNode;
	ai.m_nodes = m_nodes;
	m_registry.assign<decltype(ai)>(entity, std::move(ai));

	return entity;
}
