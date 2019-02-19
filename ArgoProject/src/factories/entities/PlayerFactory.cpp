#include "stdafx.h"
#include "utilities/cute_c2.h"
#include "PlayerFactory.h"

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
#include "components/DoubleJump.h"
#include "components/Dashable.h"

#include "commands/MoveCommand.h"
#include "commands/JumpCommand.h"
#include "commands/DashCommand.h"
#include "commands/FaceLeftCommand.h"
#include "commands/FaceRightCommand.h"
#include "commands/DropCommand.h"
#include "components/StateMachine.h"
#include "components/Health.h"

app::fact::PlayerFactory::PlayerFactory()
	: EntityFactory()
{
}

app::Entity const app::fact::PlayerFactory::create()
{
	app::Entity const entity = EntityFactory::create();

	auto location = comp::Location();
	location.position = { 900.0f, 100.0f };
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = { 100.0f, 100.0f };
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

	auto input = comp::Input();
	input.isRight = true;
	//Here is where commands get binded to keys
	input.keyDownCommands.insert(std::pair(SDLK_RIGHT, std::make_shared<app::cmnd::MoveCommand>(entity, 0, 20)));
	input.keyDownCommands.insert(std::pair(SDLK_LEFT, std::make_shared<app::cmnd::MoveCommand>(entity, 180, 20)));
	input.keyPressedCommands.insert(std::pair(SDLK_SPACE, std::make_shared<app::cmnd::JumpCommand>(entity, 400.0f)));
	input.keyPressedCommands.insert(std::pair(SDLK_z, std::make_shared<app::cmnd::DashCommand>(entity)));
	input.keyPressedCommands.insert(std::pair(SDLK_RIGHT, std::make_shared<app::cmnd::FaceRightCommand>(entity)));
	input.keyPressedCommands.insert(std::pair(SDLK_LEFT, std::make_shared<app::cmnd::FaceLeftCommand>(entity)));
	input.keyDownCommands.insert(std::pair(SDLK_DOWN, std::make_shared<app::cmnd::DropCommand>(entity)));
	m_registry.assign<decltype(input)>(entity, std::move(input));

	auto doubleJump = comp::DoubleJump();
	doubleJump.canDoubleJump = true;
	m_registry.assign<decltype(doubleJump)>(entity, std::move(doubleJump));

	auto dashable = comp::Dashable();
	dashable.canDash = true;
	m_registry.assign<decltype(dashable)>(entity, std::move(dashable));

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

	return entity;
}
