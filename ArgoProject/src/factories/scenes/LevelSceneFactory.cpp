#include "stdafx.h"
#include "LevelSceneFactory.h"
#include "factories/entities/PlayerFactory.h"
#include "factories/entities/CameraFactory.h"
#include "factories/LevelFactory.h"

std::vector<app::Entity> app::fact::sce::LevelSceneFactory::create()
{
	auto entities = std::vector<app::Entity>();

	auto player = fact::PlayerFactory().create();
	auto level = fact::LevelFactory().create();	
	entities.insert(entities.end(), level.begin(), level.end());
	entities.push_back(player);
	auto cameraParams = app::par::CameraParameters();
	cameraParams.targetEntity = player;
	cameraParams.clampRect = math::Rectf({ -800.0f, 500.0f }, { 2000.0f, 1000.0f });
	cameraParams.internalClamp = math::Vector2f(20.0f, 60.0f);
	entities.push_back(fact::CameraFactory(std::move(cameraParams)).create());

	return entities;
}
