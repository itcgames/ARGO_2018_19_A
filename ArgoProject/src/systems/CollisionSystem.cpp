#include "stdafx.h"
#include "CollisionSystem.h"
#include "Registry.h"

// components
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Render.h"
#include "components/Collision.h"

app::sys::CollisionSystem::CollisionSystem()
	: BaseSystem()
{

}

void app::sys::CollisionSystem::update(app::time::seconds const & dt)
{
	auto manifold = cute::c2Manifold();
	m_registry.view<comp::Collision>()
		.each([&, this](app::Entity const entity, comp::Collision & collision)
	{
		m_registry.view<comp::Collision>()
			.each([&, this](app::Entity const secEntity, comp::Collision & secCollision)
		{
			if (entity != secEntity)
			{
				cute::c2AABBtoAABBManifold(collision.aabb, secCollision.aabb, &manifold);
				if (manifold)
				{
					// collision has occurred
				}
			}
		});
	});
}
