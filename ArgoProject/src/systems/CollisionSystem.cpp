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
	, m_staticUpdateOnce(false)
{

}

void app::sys::CollisionSystem::update(app::time::seconds const & dt)
{
	//std::string manifoldType;
	////prepare these components
	//m_registry.prepare<comp::Collision, comp::Location, comp::Input, comp::Dimensions>();
	////view player
	//m_registry.view<comp::Collision, comp::Input, comp::Location, comp::Dimensions>(entt::persistent_t())
	//	.each([&, this](app::Entity const entity, comp::Collision & collision, comp::Input & input, comp::Location & location, comp::Dimensions & dimensions)
	//{
	//	//update collision boxes
	//	updateAABB(std::get<cute::c2AABB>(collision.collisionBox), location.position, dimensions.size);
	//	//view everything with collisions
	//	m_registry.view<comp::Collision, comp::Location, comp::Dimensions>(entt::persistent_t())
	//		.each([&, this](app::Entity const secEntity, comp::Collision & secCollision, comp::Location & secLocation, comp::Dimensions & secDimensions)
	//	{
	//		//if we are not the player
	//		if (entity != secEntity)
	//		{
	//			if (m_staticUpdateOnce == false)
	//			{
	//				m_staticUpdateOnce = true;
	//				updateAABB(std::get<cute::c2AABB>(secCollision.collisionBox), secLocation.position, secDimensions.size);
	//			}
	//			//manifoldType = checkManifoldType(collision.collisionBox, secCollision.collisionBox);
	//			//if (manifoldType == "AABBVSAABB")
	//			//{
	//			////	std::cout << "Position: " << location.position.x/* - dimensions.size.x / 2*/ << std::endl;
	//			//	//get manifold of AABB to AABB
	//			//	cute::c2Manifold manifold;
	//			//	cute::c2AABBtoAABBManifold(std::get<cute::c2AABB>(collision.collisionBox), std::get<cute::c2AABB>(secCollision.collisionBox), &manifold);
	//			//	if (manifold.count)
	//			//	{
	//			//		// collision has occurred
	//			//		auto const & direction = math::Vector2f{ manifold.n.x, manifold.n.y };
	//			//		auto const & penetration = manifold.depths[0];
	//			//		location.position -= direction * penetration;
	//			//	}
	//			//}
	//		}
	//	});
	//});
}

std::string app::sys::CollisionSystem::checkManifoldType(std::variant<cute::c2AABB, cute::c2Circle> &left, std::variant<cute::c2AABB, cute::c2Circle> &right)
{
	int num1 = left.index();
	int num2 = right.index();
	std::string s = "";
	if (num1 == 0 && num2 == 0)
	{
		s = "AABBVSAABB";
	}
	return s;
}

void app::sys::CollisionSystem::updateAABB(cute::c2AABB &c, app::math::Vector2<float> l, app::math::Vector2<float> d)
{
	c.min.x = l.x;
	c.min.y = l.y;
	c.max.x = l.x + d.x;
	c.max.y = l.y + d.y;
}

