#include "stdafx.h"
#include "CollisionCircleBoolVisitor.h"

app::vis::CollisionCircleBoolVisitor::CollisionCircleBoolVisitor(bool & collided, cute::c2Circle const & circle)
	: m_result(collided)
	, m_circle(circle)
{
}

void app::vis::CollisionCircleBoolVisitor::operator()(cute::c2AABB const & aabb)
{
	m_result = static_cast<bool>(cute::c2CircletoAABB(m_circle, aabb));
}

void app::vis::CollisionCircleBoolVisitor::operator()(cute::c2Circle const & circle)
{
	m_result = static_cast<bool>(cute::c2CircletoCircle(m_circle, circle));
}

void app::vis::CollisionCircleBoolVisitor::operator()(cute::c2Ray const & ray)
{
	auto raycast = cute::c2Raycast();
	m_result = static_cast<bool>(cute::c2RaytoCircle(ray, m_circle, &raycast));
}

void app::vis::CollisionCircleBoolVisitor::operator()(cute::c2Capsule const & capsule)
{
	m_result = static_cast<bool>(cute::c2CircletoCapsule(m_circle, capsule));
}
