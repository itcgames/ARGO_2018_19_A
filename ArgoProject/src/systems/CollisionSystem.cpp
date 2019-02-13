#include "stdafx.h"
#include "CollisionSystem.h"

// components
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Collision.h"
#include "components/Impenetrable.h"
#include "components/Platform.h"
#include "components/Player.h"
#include "components/CurrentGround.h"
#include "components/Input.h"
#include "components/Motion.h"
#include "components/AirMotion.h"
#include "components/Dash.h"
#include "components/Damage.h"
#include "components/Health.h"
//visitors
#include "visitors/CollisionUpdateVisitor.h"
#include "visitors/CollisionBoundsManiVisitor.h"
#include "visitors/CollisionBoundsBoolVisitor.h"

app::sys::CollisionSystem::CollisionSystem()
	: BaseSystem()
{
	//prepare these components
	m_registry.prepare<comp::Collision, comp::Input, comp::Location, comp::Dimensions, comp::Motion>();
	m_registry.prepare<comp::Collision, comp::Input, comp::Location, comp::Dimensions, comp::AirMotion>();
	m_registry.prepare<comp::Collision, comp::Location, comp::Dimensions>();
}

void app::sys::CollisionSystem::update(app::time::seconds const & dt)
{
	updateCollisionBoxes();
	groundCollisions();
	airCollisions();
	checkPlatformCollisions();
	dashCollisions();
	playerHazardCollisions();
}

void app::sys::CollisionSystem::groundCollisions()
{
	//view player
	m_registry.view<comp::Collision, comp::Input, comp::Location, comp::Dimensions, comp::Motion>(entt::persistent_t())
		.each([&, this](app::Entity const entity, comp::Collision & collision, comp::Input & input, comp::Location & location, comp::Dimensions & dimensions, comp::Motion & motion)
	{
		//view everything with collisions
		m_registry.view<comp::Collision, comp::Impenetrable>()
			.each([&, this](app::Entity const secEntity, comp::Collision & secCollision, comp::Impenetrable const & secImpenetrable)
		{
			//if we are not the player
			if (entity != secEntity)
			{
				//if we collide
				cute::c2Manifold const & manifold = app::vis::CollisionBoundsManiVisitor::collisionBetween(collision.bounds, secCollision.bounds);
				if (manifold.count)
				{
					// collision has occurred
					auto const & direction = math::Vector2f{ manifold.n.x, manifold.n.y };
					auto const & penetration = manifold.depths[0];
					auto const & pushback = (direction*penetration);
					location.position += pushback;
					std::visit(vis::CollisionUpdateVisitor{ location, dimensions}, collision.bounds);

					if constexpr (DEBUG_MODE)
					{
						Console::writeLine({ "Collision ", pushback, "]" });
					}
				}
			}
		});
	});
}

void app::sys::CollisionSystem::airCollisions()
{
	//view player
	m_registry.view<comp::Collision, comp::Input, comp::Location, comp::Dimensions, comp::AirMotion>(entt::persistent_t())
		.each([&, this](app::Entity const entity, comp::Collision & collision, comp::Input & input, comp::Location & location, comp::Dimensions & dimensions, comp::AirMotion & airMotion)
	{
		//view everything with collisions
		m_registry.view<comp::Collision, comp::Impenetrable>()
			.each([&, this](app::Entity const secEntity, comp::Collision & secCollision, comp::Impenetrable const & secImpenetrable)
		{
			//if we are not the player
			if (entity != secEntity)
			{
				//if we collide
				auto const & manifold = app::vis::CollisionBoundsManiVisitor::collisionBetween(collision.bounds, secCollision.bounds);
				if (manifold.count)
				{
					// collision has occurred
					auto const & direction = math::Vector2f{ manifold.n.x, manifold.n.y };
					auto const & penetration = manifold.depths[0];
					location.position += direction * penetration;

					std::visit(vis::CollisionUpdateVisitor{ location, dimensions }, collision.bounds);
				}
			}
		});
	});
}

void app::sys::CollisionSystem::checkPlatformCollisions()
{
	//view player
	m_registry.view<comp::Collision, comp::Input, comp::Location, comp::Dimensions, comp::AirMotion, comp::CurrentGround>(entt::persistent_t())
		.each([&, this](app::Entity const entity, comp::Collision & collision, comp::Input & input, comp::Location & location, comp::Dimensions & dimensions,
			comp::AirMotion & airMotion, comp::CurrentGround & ground)
	{
		//view everything with collisions
		m_registry.view<comp::Collision, comp::Location, comp::Dimensions, comp::Platform>()
			.each([&, this](app::Entity const secEntity, comp::Collision & secCollision, comp::Location & secLocation, comp::Dimensions & secDimensions, comp::Platform const & secPlatform)
		{
			//if we are not the player
			if (entity != secEntity)
			{
					//if we collide
					auto const & manifold = app::vis::CollisionBoundsManiVisitor::collisionBetween(collision.bounds, secCollision.bounds);
					if (manifold.count)
					{
						if (location.position.y + (dimensions.size.y / 2) < secLocation.position.y - (secDimensions.size.y / 2) + 10.0f)
						{
							// collision has occurred
							if (manifold.n.y == -1 && math::toVector(airMotion.direction).y > 0)
							{
								auto const & direction = math::Vector2f{ manifold.n.x, manifold.n.y };
								auto const & penetration = manifold.depths[0];
								location.position += direction * penetration;

								ground.currentGround = secEntity;
								auto groundMotion = comp::Motion();
								groundMotion.speed = airMotion.speed;
								groundMotion.direction = airMotion.direction;
								groundMotion.maxSpeed = 300.0f;
								groundMotion.drag = 0.95f;
								groundMotion.dragCutoff = 20.0f;
								input.m_canDoubleJump = true;
								input.m_canDash = true;

								auto const & velocity = ((math::toVector(groundMotion.direction) * groundMotion.speed) * math::Vector2f(1.0f, 0.0f));
								groundMotion.direction = velocity.toAngle();
								groundMotion.speed = velocity.magnitude();


								m_registry.assign<comp::Motion>(entity, std::move(groundMotion));
								m_registry.remove<comp::AirMotion>(entity);

								std::visit(vis::CollisionUpdateVisitor{ location, dimensions }, collision.bounds);
							}
						}
					}
			}
		});
	});
}

void app::sys::CollisionSystem::dashCollisions()
{
}

void app::sys::CollisionSystem::updateCollisionBoxes()
{
	m_registry.view<comp::Collision, comp::Location, comp::Dimensions>(entt::persistent_t())
		.each([&, this](app::Entity const entity, comp::Collision & collision, comp::Location & location, comp::Dimensions & dimensions)
	{
		std::visit(vis::CollisionUpdateVisitor{ location, dimensions }, collision.bounds);
	});
}


void app::sys::CollisionSystem::playerHazardCollisions()
{
	m_registry.view<comp::Collision, comp::Input, comp::Location, comp::Dimensions, comp::Health>(entt::persistent_t())
		.each([&, this](app::Entity const entity, comp::Collision & collision, comp::Input & input, comp::Location & location, comp::Dimensions & dimensions, comp::Health & health)
	{
		m_registry.view<comp::Collision, comp::Damage>()
			.each([&, this](app::Entity const secEntity, comp::Collision & secCollision, comp::Damage damage)
		{
			if (entity != secEntity)
			{
				auto const & collisionCheck = app::vis::CollisionBoundsBoolVisitor::collisionBetween(collision.bounds, secCollision.bounds);
				if (collisionCheck)
				{
					health.health -= damage.damage;
				}
			}
		});
	});
}