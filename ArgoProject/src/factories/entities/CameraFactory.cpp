#include "stdafx.h"
#include "CameraFactory.h"

// components
#include "components/Camera.h"

app::fact::CameraFactory::CameraFactory(app::par::CameraParameters param)
	: EntityFactory()
	, parameters(param)
{
}

app::Entity const app::fact::CameraFactory::create()
{
	app::Entity const entity = EntityFactory::create();

	auto camera = comp::Camera();
	camera.center = {  };
	camera.size = { 1366.0f, 768.0f };
	camera.target = parameters.targetEntity;
	camera.clampRect = parameters.clampRect;
	camera.internalClampSize = parameters.internalClampSize;
	m_registry.assign<decltype(camera)>(entity, std::move(camera));

	return entity;
}
