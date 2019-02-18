#include "stdafx.h"
#include "CollisionSystem.h"

// components
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Collision.h"
#include "components/Impenetrable.h"
#include "components/Platform.h"
#include "components/PlatformDrop.h"
#include "components/CurrentGround.h"
#include "components/Input.h"
#include "components/Motion.h"
#include "components/AirMotion.h"
#include "components/Dash.h"
#include "components/Damage.h"
#include "components/Health.h"
#include "components/Enemy.h"
#include "components/Dashable.h"
#include "components/DoubleJump.h"

//visitors
#include "visitors/CollisionUpdateVisitor.h"
#include "visitors/CollisionBoundsManiVisitor.h"
#include "visitors/CollisionBoundsBoolVisitor.h"

app::sys::CollisionSystem::CollisionSystem()
	: BaseSystem()
{
	//prepare these components
	m_registry.prepare<comp::Input, comp::Collision, comp::Location, comp::Dimensions, comp::AirMotion, comp::CurrentGround>();
	m_registry.prepare<comp::Collision, comp::Input, comp::Location, comp::Dimensions, comp::Motion>();
	m_registry.prepare<comp::Collision, comp::Input, comp::Location, comp::Dimensions, comp::AirMotion>();
	m_registry.prepare<comp::Collision, comp::Input, comp::Location, comp::Dimensions, comp::Dash>();
	m_registry.prepare<comp::Collision, comp::Impenetrable, comp::Location, comp::Dimensions>();
}

void app::sys::CollisionSystem::update(app::time::seconds const & dt)
{
	updateCollisionBoxes();
	groundCollisions();
	airCollisions();
	checkPlatformCollisions();
	dashCollisions();
	enemyWallCollisions();
	enemyEnemyCollisions();	
	playerHazardCollisions();
}

void app::sys::CollisionSystem::groundCollisions()
{
	//view player
	m_registry.view<comp::Collision, comp::Location, comp::Dimensions, comp::Motion>(entt::persistent_t())
		.each([&, this](app::Entity const entity, comp::Collision & collision, comp::Location & location, comp::Dimensions & dimensions, comp::Motion & motion)
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
				if (manifold.count && (manifold.depths[0] != 0.0f))
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
	auto dashJumpView = m_registry.view<comp::Dashable, comp::DoubleJump, comp::Collision, comp::Location, comp::Dimensions, comp::AirMotion, comp::CurrentGround>(entt::persistent_t());
	//view player
	m_registry.view<comp::Collision, comp::Location, comp::Dimensions, comp::AirMotion, comp::CurrentGround>(entt::persistent_t())
		.each([&, this](app::Entity const entity, comp::Collision & collision, comp::Location & location, comp::Dimensions & dimensions, comp::AirMotion & airMotion, comp::CurrentGround & ground)
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
					if (manifold.n.y == -1)
					{
						ground.currentGround = secEntity;
						auto groundMotion = comp::Motion();
						groundMotion.speed = airMotion.speed;
						groundMotion.direction = airMotion.direction;
						if (dashJumpView.contains(entity))
						{
							auto & doubleJump = dashJumpView.get<comp::DoubleJump>(entity);
							auto & dashable = dashJumpView.get<comp::Dashable>(entity);
							doubleJump.canDoubleJump = true;
							dashable.canDash = true;
						}

						auto const & velocity = ((math::toVector(groundMotion.direction) * groundMotion.speed) * math::Vector2f(1.0f, 0.0f));
						groundMotion.direction = velocity.toAngle();
						groundMotion.speed = velocity.magnitude();


						m_registry.assign<comp::Motion>(entity, std::move(groundMotion));
						m_registry.remove<comp::AirMotion>(entity);
					}
				}
			}
		});
	});
}

void app::sys::CollisionSystem::checkPlatformCollisions()
{
	auto dashJumpView = m_registry.view<comp::Dashable, comp::DoubleJump, comp::Collision, comp::Location, comp::Dimensions, comp::AirMotion, comp::CurrentGround>(entt::persistent_t());
	//view player
	m_registry.view<comp::Collision, comp::Location, comp::Dimensions, comp::AirMotion, comp::CurrentGround, comp::PlatformDrop>(entt::persistent_t())
		.each([&, this](app::Entity const entity, comp::Collision & collision, comp::Location & location, comp::Dimensions & dimensions,
			comp::AirMotion & airMotion, comp::CurrentGround & ground, comp::PlatformDrop & dropCheck)
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
							if (manifold.n.y == -1 && math::toVector(airMotion.direction).y > 0 && !dropCheck.falling)
							{
								auto const & direction = math::Vector2f{ manifold.n.x, manifold.n.y };
								auto const & penetration = manifold.depths[0];
								location.position += direction * penetration;

								ground.currentGround = secEntity;
								auto groundMotion = comp::Motion();
								groundMotion.speed = airMotion.speed;
								groundMotion.direction = airMotion.direction;
								if (dashJumpView.contains(entity))
								{
									auto & doubleJump = dashJumpView.get<comp::DoubleJump>(entity);
									auto & dashable = dashJumpView.get<comp::Dashable>(entity);
									doubleJump.canDoubleJump = true;
									dashable.canDash = true;
								}

								auto const & velocity = ((math::toVector(groundMotion.direction) * groundMotion.speed) * math::Vector2f(1.0f, 0.0f));
								groundMotion.direction = velocity.toAngle();
								groundMotion.speed = velocity.magnitude();


								m_registry.assign<comp::Motion>(entity, std::move(groundMotion));
								m_registry.remove<comp::AirMotion>(entity);

								std::visit(vis::CollisionUpdateVisitor{ location, dimensions }, collision.bounds);
							}
						}
						else
						{
							dropCheck.falling = false;
						}
					}
			}
		});
	});
}

void app::sys::CollisionSystem::dashCollisions()
{
	//view player
	m_registry.view<comp::Collision, comp::Input, comp::Location, comp::Dimensions, comp::Dash>(entt::persistent_t())
		.each([&, this](app::Entity const entity, comp::Collision & collision, comp::Input & input, comp::Location & location, comp::Dimensions & dimensions, comp::Dash & dash)
	{
		//view everything with collisions
		m_registry.view<comp::Collision, comp::Impenetrable, comp::Location, comp::Dimensions>(entt::persistent_t())
			.each([&, this](app::Entity const secEntity, comp::Collision & secCollision, comp::Impenetrable const & secImpenetrable, comp::Location & secLocation, comp::Dimensions & secDimensions)
		{
			//if we are not the player
			if (entity != secEntity)
			{
				//if we collide
				cute::c2Manifold const & manifold = app::vis::CollisionBoundsManiVisitor::collisionBetween(collision.bounds, secCollision.bounds);
				if (manifold.count && (manifold.depths[0] != 0.0f))
				{
					if (dash.direction == -180)
					{
						float const & blockSize = (secLocation.position.x - secDimensions.origin.x) + secDimensions.size.x;
						location.position.x = blockSize + dimensions.origin.x;
					}
					else if (dash.direction == 0)
					{
						float const & blockSize = (secLocation.position.x - secDimensions.origin.x);
						location.position.x = (blockSize - dimensions.origin.x);
					}
				}
			}
		});
	});
}

void app::sys::CollisionSystem::enemyWallCollisions()
{
	auto groundView = m_registry.view<comp::Location, comp::Dimensions>();
	//view enemy
	m_registry.view<comp::Collision, comp::Enemy, comp::Location, comp::Dimensions, comp::Motion, comp::CurrentGround>(entt::persistent_t())
		.each([&, this](app::Entity const entity, comp::Collision & collision, comp::Enemy & enemy, comp::Location & location, comp::Dimensions & dimensions,
			comp::Motion & motion, comp::CurrentGround & ground)
	{
		//view everything with collisions
		m_registry.view<comp::Collision, comp::Location, comp::Dimensions, comp::Impenetrable>()
			.each([&, this](app::Entity const secEntity, comp::Collision & secCollision, comp::Location & secLocation, comp::Dimensions & secDimensions, comp::Impenetrable & impenetrable)
		{
			//if we are not the player
			if (entity != secEntity)
			{
				//if we collide
				auto const & manifold = app::vis::CollisionBoundsManiVisitor::collisionBetween(collision.bounds, secCollision.bounds);
				if (manifold.count)
				{
					if (manifold.n.y == -1)
					{
						ground.currentGround = secEntity;
					}
					if (ground.currentGround.has_value() && groundView.contains(ground.currentGround.value()))
					{
						auto const &[platformLocation, platformDimensions] = groundView.get<comp::Location, comp::Dimensions>(ground.currentGround.value());
						float const & rightSide = platformLocation.position.x + (platformDimensions.size.x / 2);
						float const & leftSide = platformLocation.position.x - (platformDimensions.size.x / 2);
						if (location.position.x - (dimensions.size.x / 2) < leftSide || manifold.n.x == 1)
						{
							motion.direction = 0;
						}
						if (location.position.x + (dimensions.size.x / 2) >= rightSide || manifold.n.x == -1)
						{
							motion.direction = -180;
						}
					}
				}
			}
		});
	});
}

void app::sys::CollisionSystem::enemyEnemyCollisions()
{
	//view enemy
	m_registry.view<comp::Collision, comp::Enemy, comp::Location, comp::Dimensions, comp::Motion>(entt::persistent_t())
		.each([&, this](app::Entity const entity, comp::Collision & collision, comp::Enemy & enemy, comp::Location & location, comp::Dimensions & dimensions,
			comp::Motion & motion)
	{
		//view everything with collisions
		m_registry.view<comp::Collision, comp::Enemy, comp::Location, comp::Dimensions, comp::Motion>(entt::persistent_t())
			.each([&, this](app::Entity const secEntity, comp::Collision & secCollision, comp::Enemy & secEnemy, comp::Location & secLocation, comp::Dimensions & secDimensions,
				comp::Motion & secMotion)
		{
			//if we are not the player
			if (entity != secEntity)
			{
				//if we collide
				auto const & manifold = app::vis::CollisionBoundsManiVisitor::collisionBetween(collision.bounds, secCollision.bounds);
				if (manifold.count)
				{
					if (manifold.n.x == -1)
					{
						if (motion.direction == 0)
							motion.direction = -180;
						if (secMotion.direction == -180)
							secMotion.direction = 0;
					}
					if (manifold.n.x == 1)
					{
						if (motion.direction == -180)
							motion.direction = 0;
						if (secMotion.direction == 0)
							secMotion.direction = -180;
					}					
				}
			}
		});
	});
}

void app::sys::CollisionSystem::enemyPlayerCollisions()
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