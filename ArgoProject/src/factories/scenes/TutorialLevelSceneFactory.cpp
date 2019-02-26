#include "stdafx.h"
#include "TutorialLevelSceneFactory.h"
#include "factories/entities/PlayerFactory.h"
#include "factories/AIFactory.h"
#include "factories/entities/CameraFactory.h"
#include "factories/TutorialLevelFactory.h"

std::vector<app::Entity> app::fact::sce::TutorialLevelSceneFactory::create()
{
	auto position = math::Vector2f(0, 0);
	auto size = math::Vector2f(0, 0);

	auto entities = std::vector<app::Entity>();
	entities.reserve(50);

	auto player = fact::PlayerFactory().create();
	entities.push_back(player);

	auto level = fact::TutorialLevelFactory().create();
	entities.insert(entities.end(), level.begin(), level.end());

	auto cameraParams = app::par::CameraParameters();
	cameraParams.targetEntity = player;
	cameraParams.clampRect = math::Rectf({ -800.0f, -1000.0f }, { 4000.0f, 1200.0f });
	cameraParams.internalClamp = math::Vector2f(20.0f, 60.0f);
	entities.push_back(fact::CameraFactory(std::move(cameraParams)).create());

	return entities;
}