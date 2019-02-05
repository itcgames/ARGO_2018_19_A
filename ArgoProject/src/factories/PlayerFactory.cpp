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

app::fact::PlayerFactory::PlayerFactory(app::del::UPtrRenderer const & renderer)
	: m_texture(std::make_shared<decltype(m_texture)::element_type>())
{
	m_texture->load(renderer, "./res/Animations/test.png");
}

std::optional<app::Entity> app::fact::PlayerFactory::create()
{
	app::Entity const entity = m_registry.create();

	auto location = comp::Location();
	location.position = { 680.0f, 380.0f };
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = { 50.0f, 50.0f };
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
	animator.time = 0.0f;
	animator.currentFrame = 0u;
	auto const & frameSize = math::Vector2i{ 200, 150 };
	auto const & frameStep = math::Vector2i{ frameSize.x, 0 };
	animator.frames = {
		math::Recti{ frameStep * 0, frameSize },
		math::Recti{ frameStep * 1, frameSize },
		math::Recti{ frameStep * 2, frameSize }
	};
	animator.perFrame = 100.0f / animator.frames.size();
	m_registry.assign<decltype(animator)>(entity, std::move(animator));

	auto render = comp::Render();
	render.texture = m_texture;
	m_registry.assign<decltype(render)>(entity, std::move(render));

	auto input = comp::Input();
	//Here is where commands get binded to keys
	input.keyDownCommands.insert(std::pair(SDLK_RIGHT, std::make_shared<app::cmnd::MoveCommand>(entity, 0, 20)));
	input.keyDownCommands.insert(std::pair(SDLK_LEFT, std::make_shared<app::cmnd::MoveCommand>(entity, 180, 20)));
	input.keyDownCommands.insert(std::pair(SDLK_SPACE, std::make_shared<app::cmnd::JumpCommand>(entity, 500.0f)));

	m_registry.assign<decltype(input)>(entity, std::move(input));

	auto commandable = comp::Commandable();
	m_registry.assign<decltype(commandable)>(entity, std::move(commandable));

	return entity;
}
