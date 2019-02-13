#include "stdafx.h"
#include "CameraSystem.h"

// components
#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Render.h"
#include "components/Camera.h"

app::sys::CameraSystem::CameraSystem()
	: BaseSystem() 
{

}

void app::sys::CameraSystem::update(app::time::seconds const & dt)
{
	auto targetView = m_registry.view<comp::Location>();
	m_registry.view<comp::Camera>()
		.each([&, this](app::Entity const camEntity, comp::Camera & camera)
	{
		if (camera.target.has_value())
		{
			auto const & targetLocation = targetView.get(camera.target.value());
			math::Vector2f const & targetPosition = targetLocation.position;
			if (camera.internalClamp.has_value())
			{
				if (targetPosition.x > camera.center.x + camera.internalClamp.value().x)
				{
					camera.center.x = targetPosition.x - camera.internalClamp.value().x;
				}
				if (targetPosition.x < camera.center.x - camera.internalClamp.value().x)
				{
					camera.center.x = targetPosition.x + camera.internalClamp.value().x;
				}
				if (targetPosition.y > camera.center.y + camera.internalClamp.value().y)
				{
					camera.center.y = targetPosition.y - camera.internalClamp.value().y;
				}
				if (targetPosition.y < camera.center.y - camera.internalClamp.value().y)
				{
					camera.center.y = targetPosition.y + camera.internalClamp.value().y;
				}
			}
			else
			{
				camera.center = targetPosition;
			}
			if (camera.clampRect.has_value())
			{
				auto const & rect = camera.clampRect.value();
				if (rect.x > camera.center.x)
				{
					camera.center.x = rect.x;
				}
				if (rect.x + rect.w < camera.center.x)
				{
					camera.center.x = (rect.x + rect.w);
				}
				if (rect.y > camera.center.y)
				{
					camera.center.y = rect.y;
				}
				if (rect.y + rect.h < camera.center.y)
				{
					camera.center.y = (rect.y + rect.h);
				}
			}
		}
	});
}
