#include "stdafx.h"
#include "PlayerFactory.h"

// components
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Motion.h"
#include "components/Animator.h"
#include "components/Render.h"
#include "components/StateMachine.h"

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
	location.orientation = 45.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = { 300.0f, 300.0f };
	dimensions.origin = dimensions.size / 2.0f;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

	auto motion = comp::Motion();
	motion.speed = 0.0f;
	motion.direction = 0.0f;
	motion.angularSpeed = 60.0f;
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

	auto stateMachine = comp::StateMachine();
	stateMachine.instance = nullptr;
	m_registry.assign<decltype(stateMachine)>(entity, std::move(stateMachine));

	return entity;
}
