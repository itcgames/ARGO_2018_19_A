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
			camera.position = targetLocation.position - (camera.size / 2.0f);
			if (camera.clamp)
			{
				if (camera.clampTopLeft.x > camera.position.x - (camera.size.x / 2))
				{
					camera.position.x = camera.clampTopLeft.x + (camera.size.x / 2);
				}
				if (camera.clampTopLeft.x + camera.clampSize.x < camera.position.x + (camera.size.x / 2))
				{
					camera.position.x = (camera.clampTopLeft.x + camera.clampSize.x) - (camera.size.x / 2);
				}
				if (camera.clampTopLeft.y > camera.position.y - (camera.size.y / 2))
				{
					camera.position.y = camera.clampTopLeft.y + (camera.size.y / 2);
				}
				if (camera.clampTopLeft.y + camera.clampSize.y < camera.position.y + (camera.size.y / 2))
				{
					camera.position.y = (camera.clampTopLeft.y + camera.clampSize.y) - (camera.size.y / 2);
				}
			}
		}
	});
}
