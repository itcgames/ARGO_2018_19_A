#include "stdafx.h"
#include "MainMenuSceneFactory.h"
#include "factories/entities/CameraFactory.h"

std::vector<app::Entity> app::fact::sce::MainMenuSceneFactory::create()
{
	auto entities = std::vector<app::Entity>();

	entities.push_back(fact::CameraFactory().create());

	return entities;
}
