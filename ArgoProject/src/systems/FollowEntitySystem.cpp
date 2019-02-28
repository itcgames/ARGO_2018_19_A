#include "stdafx.h"
#include "FollowEntitySystem.h"
#include "components/Follow.h"
#include "components/Location.h"
#include "components/Camera.h"
#include "components/Facing.h"

void app::sys::FollowEntitySystem::update(app::time::seconds const & dt)
{

	auto locationView = m_registry.view<comp::Location>();
	auto cameraView = m_registry.view<comp::Camera>();
	auto facingView = m_registry.view<comp::Location, comp::Facing>();
	m_registry.view<comp::Follow, comp::Location>()
		.each([&, this](app::Entity const entity, comp::Follow & follow, comp::Location & location)
	{
		if (!m_registry.valid(follow.entity)) { return; }

		if (locationView.contains(follow.entity))
		{
			auto& entityToFollowLocation = locationView.get(follow.entity);
			if (facingView.contains(follow.entity) && !facingView.get<comp::Facing>(follow.entity).isRight)
			{
				location.position = entityToFollowLocation.position - follow.offset;
			}
			else
			{
				location.position = entityToFollowLocation.position + follow.offset;
			}
		}
		else if (cameraView.contains(follow.entity))
		{
			auto const & camera = cameraView.get(follow.entity);
			location.position = camera.center + follow.offset;
		}
	});
}
