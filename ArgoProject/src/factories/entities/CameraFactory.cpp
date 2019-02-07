#include "stdafx.h"
#include "CameraFactory.h"

// components
#include "components/Camera.h"

app::fact::CameraFactory::CameraFactory(std::optional<app::Entity> target)
	: EntityFactory()
	, m_target(target)
{
}

app::Entity const app::fact::CameraFactory::create()
{
	app::Entity const entity = EntityFactory::create();

	auto camera = comp::Camera();
	camera.position = {  };
	camera.size = { 1366.0f, 768.0f };
	camera.target = m_target;
	m_registry.assign<decltype(camera)>(entity, std::move(camera));

	return entity;
}
