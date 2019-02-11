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
	camera.position = {  };
	camera.size = { 1366.0f, 768.0f };
	camera.target = parameters.targetEntity;
	camera.clampTopLeft = parameters.clampPos;
	camera.clampSize = parameters.clampSize;
	camera.clamp = parameters.clamp;
	m_registry.assign<decltype(camera)>(entity, std::move(camera));

	return entity;
}
