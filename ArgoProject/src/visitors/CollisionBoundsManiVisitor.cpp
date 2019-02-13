#include "stdafx.h"
#include "CollisionBoundsManiVisitor.h"

#include "CollisionAabbManiVisitor.h"
#include "CollisionCircleManiVisitor.h"

app::vis::CollisionBoundsManiVisitor::CollisionBoundsManiVisitor(std::variant<cute::c2AABB, cute::c2Circle> const & bounds, cute::c2Manifold & manifold)
	: m_bounds(bounds)
	, m_manifold(manifold)
{
}

cute::c2Manifold app::vis::CollisionBoundsManiVisitor::collisionBetween(std::variant<cute::c2AABB, cute::c2Circle> const & left, std::variant<cute::c2AABB, cute::c2Circle> const & right)
{
	auto manifold = cute::c2Manifold();
	std::visit(vis::CollisionBoundsManiVisitor{ left, manifold }, right);
	return manifold;
}

void app::vis::CollisionBoundsManiVisitor::operator()(cute::c2AABB const & aabb)
{
	std::visit(vis::CollisionAabbManiVisitor{ m_manifold, aabb }, m_bounds);
}

void app::vis::CollisionBoundsManiVisitor::operator()(cute::c2Circle const & circle)
{
	std::visit(vis::CollisionCircleManiVisitor{ m_manifold, circle }, m_bounds);
}
