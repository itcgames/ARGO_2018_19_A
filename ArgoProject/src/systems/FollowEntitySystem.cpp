#include "stdafx.h"
#include "FollowEntitySystem.h"
#include "components/Follow.h"
#include "components/Location.h"
#include "components/Input.h"

void app::sys::FollowEntitySystem::update(app::time::seconds const & dt)
{

	auto locationView = m_registry.view<comp::Location>();
	auto inputView = m_registry.view<comp::Location, comp::Input>();
	m_registry.view<comp::Follow, comp::Location>()
		.each([&, this](app::Entity const entity, comp::Follow & follow, comp::Location & location)
	{
		if (m_registry.valid(follow.entity) && locationView.contains(follow.entity))
		{
			auto& entityToFollowLocation = locationView.get(follow.entity);
			if (inputView.contains(follow.entity) && !inputView.get<comp::Input>(follow.entity).isRight)
			{
				location.position = entityToFollowLocation.position - follow.offset;
			}
			else
			{
				location.position = entityToFollowLocation.position + follow.offset;
			}
		}
	});
}
