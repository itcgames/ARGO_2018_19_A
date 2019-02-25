#include "stdafx.h"
#include "LevelDemoFactory.h"

#include "factories/AIFactory.h"
#include "factories/LevelFactory.h"
#include "factories/entities/CameraFactory.h"

#include "parameters/CameraParameters.h"

#include "components/Camera.h"


app::fact::LevelDemoFactory::LevelDemoFactory(app::Entity camera)
	: m_cameraEntity(camera)
{
}

std::vector<app::Entity> app::fact::LevelDemoFactory::create()
{
	auto entities = std::vector<app::Entity>();
	auto position = math::Vector2f(0, 0);
	auto size = math::Vector2f(0, 0);

	auto ai = fact::AIFactory(position, size);

	position = app::math::Vector2f(750, 200);
	size = app::math::Vector2f(100, 100);
	auto aiEntities = ai.create();
	entities.insert(entities.end(), aiEntities.begin(), aiEntities.end());

	auto level = fact::LevelFactory().create();
	entities.insert(entities.end(), level.begin(), level.end());
	auto cameraView = m_registry.view<comp::Camera>();
	if (cameraView.contains(m_cameraEntity))
	{
		auto & camera = cameraView.get(m_cameraEntity);
		camera.target = aiEntities.back();
		camera.clampRect = math::Rectf({ -800.0f, 300.0f }, { 2000.0f, 1000.0f });
		camera.internalClamp = math::Vector2f(20.0f, 60.0f);
	}

	return entities;
}
