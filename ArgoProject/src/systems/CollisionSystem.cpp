#include "stdafx.h"
#include "CollisionSystem.h"

// components
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Collision.h"
#include "components/Input.h"
#include "components/Motion.h"
#include "components/AirMotion.h"
#include "components/Dash.h"
//visitors
#include "visitors/CollisionUpdateVisitor.h"
#include "visitors/CollisionBoundsManiVisitor.h"

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
	dashCollisions();
}

void app::sys::CollisionSystem::groundCollisions()
{
	//view player
	m_registry.view<comp::Collision, comp::Input, comp::Location, comp::Dimensions, comp::Motion>(entt::persistent_t())
		.each([&, this](app::Entity const entity, comp::Collision & collision, comp::Input & input, comp::Location & location, comp::Dimensions & dimensions, comp::Motion & motion)
	{
		//view everything with collisions
		m_registry.view<comp::Collision>()
			.each([&, this](app::Entity const secEntity, comp::Collision & secCollision)
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
		m_registry.view<comp::Collision>()
			.each([&, this](app::Entity const secEntity, comp::Collision & secCollision)
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
