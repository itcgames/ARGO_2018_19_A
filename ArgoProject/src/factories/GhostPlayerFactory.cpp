#include "stdafx.h"
#include "GhostPlayerFactory.h"

// components
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Animator.h"
#include "components/Layer.h"
#include "components/Render.h"
#include "components/StateMachine.h"
#include "components/Ghost.h"

#include "parameters/GhostPlayerFactoryParameters.h"

app::fact::GhostPlayerFactory::GhostPlayerFactory(app::par::GhostPlayerFactoryParameters const & params)
	: EntityFactory()
	, m_params(params)
{
}

app::Entity const app::fact::GhostPlayerFactory::create()
{
	app::Entity const entity = EntityFactory::create();

	auto location = comp::Location();
	location.position = m_params.position;
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = math::Vector2f{ 100, 100 };
	dimensions.origin = dimensions.size / 2.0f;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

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

	auto layer = comp::Layer();
	layer.zIndex = 90u;
	m_registry.assign<decltype(layer)>(entity, std::move(layer));

	auto render = comp::Render();
	render.texture = m_resourceManager.getTexture(app::res::TextureKey::DebugAnimation);
	m_registry.assign<decltype(render)>(entity, std::move(render));

	auto stateMachine = comp::StateMachine();
	stateMachine.instance = nullptr;
	m_registry.assign<decltype(stateMachine)>(entity, std::move(stateMachine));

	auto ghost = comp::Ghost();
	ghost.id = m_params.id;
	m_registry.assign<decltype(ghost)>(entity, std::move(ghost));

	return entity;
}
