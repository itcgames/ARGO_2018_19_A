#include "stdafx.h"
#include "CollisionAabbBoolVisitor.h"

app::vis::CollisionAabbBoolVisitor::CollisionAabbBoolVisitor(bool & collided, cute::c2AABB const & leftAabb)
	: m_result(collided)
	, m_left(leftAabb)
{
}

void app::vis::CollisionAabbBoolVisitor::operator()(cute::c2AABB const & aabb)
{
	m_result = static_cast<bool>(cute::c2AABBtoAABB(m_left, aabb));
}

void app::vis::CollisionAabbBoolVisitor::operator()(cute::c2Circle const & circle)
{
	m_result = static_cast<bool>(cute::c2CircletoAABB(circle, m_left));
}

void app::vis::CollisionAabbBoolVisitor::operator()(cute::c2Ray const & ray)
{
	auto raycast = cute::c2Raycast();
	m_result = static_cast<bool>(cute::c2RaytoAABB(ray, m_left, &raycast));
}

void app::vis::CollisionAabbBoolVisitor::operator()(cute::c2Capsule const & capsule)
{
	m_result = static_cast<bool>(cute::c2AABBtoCapsule(m_left, capsule));
}
