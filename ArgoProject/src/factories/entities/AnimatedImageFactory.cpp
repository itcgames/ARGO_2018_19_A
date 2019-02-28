#include "stdafx.h"
#include "AnimatedImageFactory.h"
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Layer.h"
#include "components/Render.h"
#include "components/Animator.h"
#include "components/AnimatedImage.h"

app::fact::AnimatedImageFactory::AnimatedImageFactory(
	app::par::AnimatedImageFactoryParameters const & params
)
	: EntityFactory()
	, m_position(params.position)
	, m_size(params.size)
	, m_origin(params.origin)
	, m_textureKey(params.textureKey)
	, m_frameSize(params.frameSize)
	, m_noFrames(params.frameNumber)
	, m_animationLoop(params.animationLoop)
	, m_zIndex(params.zIndex)
	, m_maxFrames(params.maxFrames)
{
}

app::Entity const app::fact::AnimatedImageFactory::create()
{
	app::Entity const entity = m_registry.create();

	auto location = comp::Location();
	location.position = m_position;
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = m_size;
	dimensions.origin = m_origin;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));
	
	auto animator = comp::Animator();
	animator.loop = m_animationLoop; // tell animator to loop animation when it reaches the end.
	animator.time = 0.0f; // Separate time tracking for the animation, leave it at zero
	animator.currentFrame = math::Vector2i{ 0, 0 }; // Starting frame
	animator.position = { 0, 0 }; // Starting position
	animator.frameSize = m_frameSize;
	animator.numOfFrames = m_noFrames;
	animator.maxFrames = m_maxFrames;
	// time it takes to switch from one frame to another.
	// calculating it by taking full_duration / (number of total frames)
	// while dealing with edge case of any of the frames being zero
	animator.perFrame = 90.0f / (std::max(animator.numOfFrames.x, 1) * std::max(animator.numOfFrames.y, 1));
	m_registry.assign<decltype(animator)>(entity, std::move(animator));

	auto layer = comp::Layer();
	layer.zIndex = m_zIndex;
	m_registry.assign<decltype(layer)>(entity, std::move(layer));

	auto render = comp::Render();
	render.texture = m_resourceManager.getTexture(m_textureKey);
	m_registry.assign<decltype(render)>(entity, std::move(render));

	auto animatedImage = comp::AnimatedImage();
	m_registry.assign<decltype(animatedImage)>(entity, std::move(animatedImage));
	return entity;
}
