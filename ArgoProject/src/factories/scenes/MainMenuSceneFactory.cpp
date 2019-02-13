#include "stdafx.h"
#include "MainMenuSceneFactory.h"
#include "factories/entities/CameraFactory.h"
#include "factories/entities/BackgroundImageFactory.h"
#include "factories/entities/TextFactory.h"

std::vector<app::Entity> app::fact::sce::MainMenuSceneFactory::create()
{
	auto entities = std::vector<app::Entity>();

	entities.push_back(fact::BackgroundImageFactory().create());
	entities.push_back(fact::TextFactory({ 0.0f, 0.0f }, math::Vector2f{ 300.0f, 150.0f }, "Debug Text").create());
	entities.push_back(fact::CameraFactory().create());

	return entities;
}
