#include "stdafx.h"
#include "FollowEntitySystem.h"
#include "components/FollowEntity.h"
#include "components/Location.h"
#include "components/Input.h"

void app::sys::FollowEntitySystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::FollowEntity, comp::Location>()
		.each([&, this](app::Entity const entity, comp::FollowEntity & _followEntity, comp::Location & _location)
	{
		if (m_registry.valid(_followEntity.entity) && m_registry.has<comp::Input>(_followEntity.entity))
		{
			auto& entityToFollowLocation = m_registry.get<comp::Location>(_followEntity.entity);
			auto& entityToFollowInput = m_registry.get<comp::Input>(_followEntity.entity);
			if (entityToFollowInput.isRight)
			{
				_location.position = entityToFollowLocation.position + _followEntity.offset;
			}
			else
			{
				_location.position = entityToFollowLocation.position - _followEntity.offset;
			}
		}
	});
}
