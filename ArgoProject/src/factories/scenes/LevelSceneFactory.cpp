#include "stdafx.h"
#include "LevelSceneFactory.h"
#include "factories/entities/PlayerFactory.h"
#include "factories/AIFactory.h"
#include "factories/entities/CameraFactory.h"
#include "factories/LevelFactory.h"

std::vector<app::Entity> app::fact::sce::LevelSceneFactory::create()
{
	auto position = math::Vector2f(0, 0);
	auto size = math::Vector2f(0, 0);

	auto entities = std::vector<app::Entity>();
	entities.reserve(50);

	auto player = fact::PlayerFactory().create();
	entities.push_back(player);

	auto ai = fact::AIFactory(position, size);

	position = app::math::Vector2f(750, 200);
	size = app::math::Vector2f(100, 100);
	auto aiEntities = ai.create();
	entities.insert(entities.end(), aiEntities.begin(), aiEntities.end());

	auto level = fact::LevelFactory().create();	
	entities.insert(entities.end(), level.begin(), level.end());

	auto cameraParams = app::par::CameraParameters();
	cameraParams.targetEntity = player;
	cameraParams.clampRect = math::Rectf({ -800.0f, 300.0f }, { 2000.0f, 1000.0f });
	cameraParams.internalClamp = math::Vector2f(20.0f, 60.0f);
	entities.push_back(fact::CameraFactory(std::move(cameraParams)).create());

	return entities;
}
