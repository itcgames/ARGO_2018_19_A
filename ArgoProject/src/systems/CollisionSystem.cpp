#include "stdafx.h"
#include "CollisionSystem.h"

// components
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Render.h"
#include "components/Collision.h"
#include "components/Input.h"
#include "components/Motion.h"

app::sys::CollisionSystem::CollisionSystem()
	: BaseSystem()
{
	//prepare these components
	m_registry.prepare<comp::Collision, comp::Location, comp::Input, comp::Dimensions>();
}

void app::sys::CollisionSystem::update(app::time::seconds const & dt)
{
	//type of collision
	std::string manifoldType;

	//view player
	m_registry.view<comp::Collision, comp::Input, comp::Location, comp::Dimensions>(entt::persistent_t())
		.each([&, this](app::Entity const entity, comp::Collision & collision, comp::Input & input, comp::Location & location, comp::Dimensions & dimensions)
	{
		//update collision boxes
		updateAABB(std::get<cute::c2AABB>(collision.collisionBox), location.position, dimensions.size, dimensions.origin);
		//view everything with collisions
		m_registry.view<comp::Collision, comp::Location, comp::Dimensions>(entt::persistent_t())
			.each([&, this](app::Entity const secEntity, comp::Collision & secCollision, comp::Location & secLocation, comp::Dimensions & secDimensions)
		{
			//if we are not the player
			if (entity != secEntity)
			{
				updateAABB(std::get<cute::c2AABB>(secCollision.collisionBox), secLocation.position, secDimensions.size, secDimensions.origin);
				
				manifoldType = checkManifoldType(collision.collisionBox, secCollision.collisionBox);
				//if square to square 
				if (manifoldType == "AABBVSAABB")
				{
				//	std::cout << "Position: " << location.position.x/* - dimensions.size.x / 2*/ << std::endl;
					//get manifold of AABB to AABB
					cute::c2Manifold manifold;
					cute::c2AABBtoAABBManifold(std::get<cute::c2AABB>(secCollision.collisionBox), std::get<cute::c2AABB>(collision.collisionBox), &manifold);
					if (manifold.count)
					{
						// collision has occurred
						auto const & direction = math::Vector2f{ manifold.n.x, manifold.n.y };
						auto const & penetration = manifold.depths[0];
						location.position += (direction * penetration);
					}
				}
			}
		});
	});
}

std::string app::sys::CollisionSystem::checkManifoldType(std::variant<cute::c2AABB, cute::c2Circle> &left, std::variant<cute::c2AABB, cute::c2Circle> &right)
{
	//the index is the index of the variant of the type were using  so 0 is square 1 is circle
	int num1 = left.index();
	int num2 = right.index();
	std::string s = "";
	if (num1 == 0 && num2 == 0)
	{
		s = "AABBVSAABB";
	}
	return s;
}

void app::sys::CollisionSystem::updateAABB(cute::c2AABB &c, app::math::Vector2f l, app::math::Vector2f d, app::math::Vector2f o)
{
	//update the collision boxes
	c.min.x = l.x - o.x;
	c.min.y = l.y - o.y;
	c.max.x = c.min.x + d.x;
	c.max.y = c.min.y + d.y;
}

