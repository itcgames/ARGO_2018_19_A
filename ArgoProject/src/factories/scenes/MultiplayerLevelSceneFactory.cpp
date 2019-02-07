#include "stdafx.h"
#include "MultiplayerLevelSceneFactory.h"
#include "factories/entities/PlayerFactory.h"
#include "factories/entities/CameraFactory.h"
#include "factories/LevelFactory.h"

app::fact::sce::MultiplayerLevelSceneFactory::MultiplayerLevelSceneFactory()
	: EntitiesFactory()
{
}

std::vector<app::Entity> app::fact::sce::MultiplayerLevelSceneFactory::create()
{
	auto entities = std::vector<app::Entity>();

	auto player = fact::PlayerFactory().create();
	auto level = fact::LevelFactory().create();	
	entities.insert(entities.end(), level.begin(), level.end());
	entities.push_back(player);
	entities.push_back(fact::CameraFactory(player).create());

	return entities;
}
