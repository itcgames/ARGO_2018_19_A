#include "stdafx.h"
#include "CollisionCircleManiVisitor.h"

app::vis::CollisionCircleManiVisitor::CollisionCircleManiVisitor(cute::c2Manifold & manifold, cute::c2Circle const & circle)
	: m_manifold(manifold)
	, m_circle(circle)
{
}

void app::vis::CollisionCircleManiVisitor::operator()(cute::c2AABB const & aabb)
{
	cute::c2CircletoAABBManifold(m_circle, aabb, &m_manifold);
}

void app::vis::CollisionCircleManiVisitor::operator()(cute::c2Circle const & circle)
{
	cute::c2CircletoCircleManifold(m_circle, circle, &m_manifold);
}
