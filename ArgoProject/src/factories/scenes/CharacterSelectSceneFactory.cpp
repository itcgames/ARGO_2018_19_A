#include "stdafx.h"
#include "CharacterSelectSceneFactory.h"
#include "factories/entities/CameraFactory.h"

std::vector<app::Entity> app::fact::sce::CharacterSelectSceneFactory::create()
{
	auto entities = std::vector<app::Entity>();

	entities.push_back(fact::CameraFactory().create());

	return entities;
}
