#include "stdafx.h"
#include "MainMenuSceneFactory.h"
#include "factories/entities/CameraFactory.h"
#include "factories/entities/BackgroundImageFactory.h"
#include "factories/entities/ButtonFactory.h"
#include "factories/entities/TextFactory.h"

#include "commands/TestCommand.h"

std::vector<app::Entity> app::fact::sce::MainMenuSceneFactory::create()
{
	auto entities = std::vector<app::Entity>();

	{
		auto const & sizePerLetter = math::Vector2f{ 20.0f, 40.0f };
		auto params = app::par::ButtonFactoryParameters();
		params.position = math::Vector2f{ 0.0f, 0.0f };
		params.text = std::string("This is a button");
		auto const & stepSize = math::Vector2f{ static_cast<float>(params.text.size()), 1.0f };
		params.size = (sizePerLetter * stepSize);
		params.border = math::Vector2f{ 20.0f, 4.0f };
		params.command = std::make_unique<cmnd::TestCommand>();
		entities.push_back(fact::ButtonFactory(params).create());
	}
	{
		auto const & position = math::Vector2f{ 0.0f, 200.0f };
		auto const & sizePerLetter = math::Vector2f{ 20.0f, 40.0f };
		auto const & text = std::string("Are you not entertained!");
		auto const & stepSize = math::Vector2f{ static_cast<float>(text.size()), 1.0f };
		entities.push_back(fact::TextFactory(position, sizePerLetter * stepSize, text).create());
	}
	{
		auto const & size = math::Vector2f{ 1366.0f, 768.0f };
		auto const & origin = size / 2.0f;
		auto const & position = math::Vector2f{ 0.0f, 0.0f };
		auto const & textureKey = app::res::TextureKey::Debug;
		entities.push_back(fact::BackgroundImageFactory(position, size, origin, textureKey).create());
	}
	entities.push_back(fact::CameraFactory().create());

	return entities;
}
