#include "stdafx.h"
#include "utilities/cute_c2.h"
#include "EnemyFactory.h"

// components
#include "components/Health.h"
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Motion.h"
#include "components/Animator.h"
#include "components/Render.h"
#include "components/Collision.h"
#include "components/CurrentGround.h"
#include "components/Enemy.h"

app::fact::EnemyFactory::EnemyFactory(math::Vector2f const & position, math::Vector2f const & size)
	: EntityFactory()
	, m_position(position)
	, m_size(size)
{
}

app::Entity const app::fact::EnemyFactory::create()
{
	app::Entity const entity = EntityFactory::create();

	auto health = comp::Health();
	health.health = 1;
	m_registry.assign<decltype(health)>(entity, std::move(health));

	auto location = comp::Location();
	location.position = m_position;
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = m_size;
	dimensions.origin = dimensions.size / 2.0f;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

	auto motion = comp::Motion();
	motion.speed = 50.0f;
	motion.direction = -180.0f;
	motion.angularSpeed = 0.0f;
	motion.drag = 1.0f;
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
	render.texture = m_resourceManager.getTexture(app::res::TextureKey::DebugEnemyAnimation);
	m_registry.assign<decltype(render)>(entity, std::move(render));

	auto collision = comp::Collision();
	collision.bounds = cute::c2AABB();
	m_registry.assign<decltype(collision)>(entity, std::move(collision));

	auto ground = comp::CurrentGround();
	m_registry.assign<decltype(ground)>(entity, std::move(ground));

	auto enemy = comp::Enemy();
	m_registry.assign<decltype(enemy)>(entity, std::move(enemy));

	return entity;
}
