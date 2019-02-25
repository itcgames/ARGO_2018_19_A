#include "stdafx.h"
#include "FollowEntitySystem.h"
#include "components/FollowEntity.h"
#include "components/Location.h"
#include "components/Input.h"

void app::sys::FollowEntitySystem::update(app::time::seconds const & dt)
{

	m_registry.view<comp::FollowEntity, comp::Location>()
		.each([&, this](app::Entity const entity, comp::FollowEntity & followEntity, comp::Location & location)
	{
		auto inputView = m_registry.view<comp::Input>();
		if (m_registry.valid(followEntity.entity) && inputView.contains(followEntity.entity))
		{
			auto& entityToFollowLocation = m_registry.get<comp::Location>(followEntity.entity);
			auto& entityToFollowInput = m_registry.get<comp::Input>(followEntity.entity);
			if (entityToFollowInput.isRight)
			{
				location.position = entityToFollowLocation.position + followEntity.offset;
			}
			else
			{
				location.position = entityToFollowLocation.position - followEntity.offset;
			}
		}
	});
}
