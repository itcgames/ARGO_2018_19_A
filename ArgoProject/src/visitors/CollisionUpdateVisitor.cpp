#include "stdafx.h"
#include "CollisionUpdateVisitor.h"
#include "math/Math.h"

app::vis::CollisionUpdateVisitor::CollisionUpdateVisitor(comp::Location const & location, comp::Dimensions const & dimensions)
	: m_location(location)
	, m_dimensions(dimensions)
{
}

void app::vis::CollisionUpdateVisitor::operator()(cute::c2AABB & aabb) const
{
	if constexpr (true)
	{
		aabb.min.x = m_location.position.x - m_dimensions.origin.x;
		aabb.min.y = m_location.position.y - m_dimensions.origin.y;
		aabb.max.x = aabb.min.x + m_dimensions.size.x;
		aabb.max.y = aabb.min.y + m_dimensions.size.y;
	}
	else if constexpr (false)
	{
		const auto rotatedOrigin = math::rotate(m_dimensions.origin, m_location.orientation);
		const auto rotatedSize = math::rotate(m_dimensions.size, m_location.orientation);
		aabb.min.x = m_location.position.x - rotatedOrigin.x;
		aabb.min.y = m_location.position.y - rotatedOrigin.y;
		aabb.max.x = aabb.min.x + rotatedSize.x;
		aabb.max.y = aabb.min.y + rotatedSize.y;
	}
}

void app::vis::CollisionUpdateVisitor::operator()(cute::c2Circle & circle) const
{
	circle.p.x = m_location.position.x; circle.p.y = m_location.position.y;
	circle.r = m_dimensions.size.x > m_dimensions.size.y ? m_dimensions.size.x : m_dimensions.size.y;
}
