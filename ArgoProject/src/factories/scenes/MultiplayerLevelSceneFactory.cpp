#include "stdafx.h"
#include "MultiplayerLevelSceneFactory.h"
#include "factories/entities/PlayerFactory.h"
#include "factories/entities/CameraFactory.h"
#include "factories/LevelFactory.h"
#include "factories/GhostPlayerFactory.h"
#include "parameters/GhostPlayerFactoryParameters.h"

std::vector<app::Entity> app::fact::sce::MultiplayerLevelSceneFactory::create()
{
	auto position = math::Vector2f(0, 0);
	auto size = math::Vector2f(0, 0);

	auto entities = std::vector<app::Entity>();
	entities.reserve(50);

	auto player = fact::PlayerFactory().create();
	entities.push_back(player);

	auto level = fact::LevelFactory().create();	
	entities.insert(entities.end(), level.begin(), level.end());

	//GHOST PLAYERS
	auto params = app::par::GhostPlayerFactoryParameters();
	{
		params.position = math::Vector2f(900, 100);
		params.id = entities.size();
		entities.push_back(fact::GhostPlayerFactory(params).create());
	}
	{
		params.position = math::Vector2f(920, 100);
		params.id = entities.size();
		entities.push_back(fact::GhostPlayerFactory(params).create());
	}
	{
		params.position = math::Vector2f(930, 100);
		params.id = entities.size();
		entities.push_back(fact::GhostPlayerFactory(params).create());
	}
	auto cameraParams = app::par::CameraParameters();
	cameraParams.targetEntity = player;
	cameraParams.clampRect = math::Rectf({ -800.0f, 300.0f }, { 2000.0f, 1000.0f });
	cameraParams.internalClamp = math::Vector2f(20.0f, 60.0f);
	entities.push_back(fact::CameraFactory(std::move(cameraParams)).create());

	return entities;
}
