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
	entities.push_back(fact::CameraFactory(app::par::CameraParameters{ player, math::Rectf(app::math::Vector2f(-800, 500), app::math::Vector2f(2000, 1000)), true, 20 }).create());

	return entities;
}
