#include "stdafx.h"
#include "PlayerFactory.h"

// components
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Motion.h"
#include "components/Animator.h"
#include "components/Render.h"
#include "components/Input.h"
#include "components/Commandable.h"

#include "commands/MoveCommand.h"
#include "commands/JumpCommand.h"
#include "commands/DashCommand.h"
#include "commands/FaceLeftCommand.h"
#include "commands/FaceRightCommand.h"
#include "components/StateMachine.h"

app::fact::PlayerFactory::PlayerFactory()
	: EntityFactory()
	, m_texture(std::make_shared<decltype(m_texture)::element_type>())
{
	m_texture->load(m_renderer, "./res/Animations/test.png");
}

app::Entity const app::fact::PlayerFactory::create()
{
	app::Entity const entity = EntityFactory::create();

	auto location = comp::Location();
	location.position = { 680.0f, 380.0f };
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = { 100.0f, 100.0f };
	dimensions.origin = dimensions.size / 2.0f;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

	auto motion = comp::Motion();
	motion.speed = 0.0f;
	motion.direction = 0.0f;
	motion.angularSpeed = 0.0f;
	motion.drag = 0.95f;
	motion.dragCutoff = 20.0f;
	motion.maxSpeed = 300.0f;
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
	render.texture = m_texture;
	m_registry.assign<decltype(render)>(entity, std::move(render));

	auto input = comp::Input();
	input.m_isRight = true;
	input.m_canDoubleJump = true;
	input.m_canDash = true;
	//Here is where commands get binded to keys
	input.keyDownCommands.insert(std::pair(SDLK_RIGHT, std::make_shared<app::cmnd::MoveCommand>(entity, 0, 20)));
	input.keyDownCommands.insert(std::pair(SDLK_LEFT, std::make_shared<app::cmnd::MoveCommand>(entity, 180, 20)));
	input.keyPressedCommands.insert(std::pair(SDLK_SPACE, std::make_shared<app::cmnd::JumpCommand>(entity, 400.0f)));
	input.keyPressedCommands.insert(std::pair(SDLK_z, std::make_shared<app::cmnd::DashCommand>(entity)));
	input.keyPressedCommands.insert(std::pair(SDLK_RIGHT, std::make_shared<app::cmnd::FaceRightCommand>(entity)));
	input.keyPressedCommands.insert(std::pair(SDLK_LEFT, std::make_shared<app::cmnd::FaceLeftCommand>(entity)));


	m_registry.assign<decltype(input)>(entity, std::move(input));

	auto commandable = comp::Commandable();
	m_registry.assign<decltype(commandable)>(entity, std::move(commandable));
	auto stateMachine = comp::StateMachine();
	stateMachine.instance = nullptr;
	m_registry.assign<decltype(stateMachine)>(entity, std::move(stateMachine));

	return entity;
}
