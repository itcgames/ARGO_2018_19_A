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
			math::Vector2f targetPosition = targetLocation.position;
			if (camera.internalClampSize.has_value())
			{
				math::Vector2f clampPosition;
				bool followPlayerX = false;
				bool followPlayerY = false;
				if (targetPosition.x > camera.center.x + camera.internalClampSize.value())
				{
					clampPosition.x = targetPosition.x - camera.internalClampSize.value();
					followPlayerX = true;
				}
				if (targetPosition.x < camera.center.x - camera.internalClampSize.value())
				{
					clampPosition.x = targetPosition.x + camera.internalClampSize.value();
					followPlayerX = true;
				}
				if (targetPosition.y > camera.center.y + camera.internalClampSize.value())
				{
					clampPosition.y = targetPosition.y - camera.internalClampSize.value();
					followPlayerY = true;
				}
				if (targetPosition.y < camera.center.y - camera.internalClampSize.value())
				{
					clampPosition.y = targetPosition.y + camera.internalClampSize.value();
					followPlayerY = true;
				}
				if (followPlayerX)
				{
					camera.center.x = clampPosition.x;
				}
				if (followPlayerY)
				{
					camera.center.y = clampPosition.y;
				}
			}
			else
			{
				camera.center = targetPosition;
			}
			//camera.position = targetLocation.position - (camera.size / 2.0f);
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
