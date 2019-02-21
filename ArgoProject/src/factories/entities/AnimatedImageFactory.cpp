#include "stdafx.h"
#include "AnimatedImageFactory.h"
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Render.h"
#include "components/Animator.h"
#include "components/AnimatedImage.h"

app::fact::AnimatedImageFactory::AnimatedImageFactory(
	math::Vector2f const & position
	, math::Vector2f const & size
	, math::Vector2f const & origin
	, app::res::TextureKey const & textureKey
	, math::Vector2f const & frameSize
	, math::Vector2f const & noFrames
)
	: EntityFactory()
	, m_position(position)
	, m_size(size)
	, m_origin(origin)
	, m_textureKey(textureKey)
	, m_frameSize(frameSize)
	, m_noFrames(noFrames)
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
	animator.loop = false; // tell animator to loop animation when it reaches the end.
	animator.time = 0.0f; // Separate time tracking for the animation, leave it at zero
	animator.currentFrame = math::Vector2i{ 0, 0 }; // Starting frame
	animator.position = { 0, 0 }; // Starting position
	animator.frameSize = m_frameSize;
	animator.numOfFrames = m_noFrames;
	// time it takes to switch from one frame to another.
	// calculating it by taking full_duration / (number of total frames)
	// while dealing with edge case of any of the frames being zero
	animator.perFrame = 90.0f / (std::max(animator.numOfFrames.x, 1) * std::max(animator.numOfFrames.y, 1));
	m_registry.assign<decltype(animator)>(entity, std::move(animator));

	auto render = comp::Render();
	render.texture = m_resourceManager.getTexture(m_textureKey);
	m_registry.assign<decltype(render)>(entity, std::move(render));

	auto animatedImage = comp::AnimatedImage();
	m_registry.assign<decltype(animatedImage)>(entity, std::move(animatedImage));
	return entity;
}
