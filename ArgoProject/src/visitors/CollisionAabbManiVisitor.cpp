#include "stdafx.h"
#include "CollisionAabbManiVisitor.h"

app::vis::CollisionAabbManiVisitor::CollisionAabbManiVisitor(cute::c2Manifold & manifold, cute::c2AABB const & aabb)
	: m_manifold(manifold)
	, m_aabb(aabb)
{
}

void app::vis::CollisionAabbManiVisitor::operator()(cute::c2AABB const & aabb)
{
	cute::c2AABBtoAABBManifold(m_aabb, aabb, &m_manifold);
}

void app::vis::CollisionAabbManiVisitor::operator()(cute::c2Circle const & circle)
{
	cute::c2CircletoAABBManifold(circle, m_aabb, &m_manifold);
}
