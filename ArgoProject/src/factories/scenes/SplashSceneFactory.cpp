#include "stdafx.h"
#include "SplashSceneFactory.h"
#include "factories/entities/PlayerFactory.h"
#include "factories/entities/CameraFactory.h"

app::fact::sce::SplashSceneFactory::SplashSceneFactory()
	: EntitiesFactory()
{
}

std::vector<app::Entity> app::fact::sce::SplashSceneFactory::create()
{
	auto entities = std::vector<app::Entity>();

	auto player = fact::PlayerFactory().create();
	entities.push_back(player);
	entities.push_back(fact::CameraFactory(player).create());

	return entities;
}
