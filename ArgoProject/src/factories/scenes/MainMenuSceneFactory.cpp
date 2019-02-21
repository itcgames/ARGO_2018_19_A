#include "stdafx.h"
#include "MainMenuSceneFactory.h"
#include "factories/entities/CameraFactory.h"
#include "factories/entities/BackgroundImageFactory.h"
#include "factories/entities/TextFactory.h"
#include "factories/entities/PlayerFactory.h"
#include "factories/AIFactory.h"
#include "factories/LevelFactory.h"

std::vector<app::Entity> app::fact::sce::MainMenuSceneFactory::create()
{
	auto entities = std::vector<app::Entity>();



	auto position = math::Vector2f(0, 0);
	auto size = math::Vector2f(0, 0);

	auto ai = fact::AIFactory(position, size);

	position = app::math::Vector2f(750, 200);
	size = app::math::Vector2f(100, 100);
	auto aiEntities = ai.create();
	entities.insert(entities.end(), aiEntities.begin(), aiEntities.end());

	auto level = fact::LevelFactory().create();
	entities.insert(entities.end(), level.begin(), level.end());

	auto cameraParams = app::par::CameraParameters();
	cameraParams.targetEntity = aiEntities.back();
	cameraParams.clampRect = math::Rectf({ -800.0f, 300.0f }, { 2000.0f, 1000.0f });
	cameraParams.internalClamp = math::Vector2f(20.0f, 60.0f);
	entities.push_back(fact::CameraFactory(std::move(cameraParams)).create());


	{
		auto const & size = math::Vector2f{ 1366.0f, 768.0f };
		auto const & origin = size / 2.0f;
		auto const & position = app::math::Vector2f(750, 200);
		auto const & textureKey = app::res::TextureKey::Debug;
		entities.push_back(fact::BackgroundImageFactory(position, size, origin, textureKey).create());
	}
	{
		auto const & position = app::math::Vector2f(750, 200);
		auto const & sizePerLetter = math::Vector2f{ 20.0f, 40.0f };
		auto const & text = std::string("Are you not entertained!");
		auto const & stepSize = math::Vector2f{ static_cast<float>(text.size()), 1.0f };
		entities.push_back(fact::TextFactory(position, sizePerLetter * stepSize, text).create());
	}
	return entities;
}
