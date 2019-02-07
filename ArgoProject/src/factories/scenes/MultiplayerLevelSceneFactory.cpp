#include "stdafx.h"
#include "MultiplayerLevelSceneFactory.h"
#include "factories/entities/CameraFactory.h"

std::vector<app::Entity> app::fact::sce::MultiplayerLevelSceneFactory::create()
{
	auto entities = std::vector<app::Entity>();

	entities.push_back(fact::CameraFactory().create());

	return entities;
}
