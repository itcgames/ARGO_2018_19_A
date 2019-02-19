#include "stdafx.h"
#include "AskNameFactory.h"
#include "commands/TestCommand.h"
#include "parameters/ButtonFactoryParameters.h"
#include "factories/entities/ButtonFactory.h"
#include "factories/entities/BackgroundImageFactory.h"

std::vector<app::Entity> app::fact::mod::AskNameFactory::create()
{
	auto entities = std::vector<app::Entity>();

	auto const & sizePerLetter = math::Vector2f{ 20.0f, 40.0f };
	{
		auto params = app::par::ButtonFactoryParameters();
		params.position = math::Vector2f{ -300.0f, 80.0f };
		params.state = app::comp::Presseable::State::Highlighted;
		params.text = std::string("Confirm");
		auto const & stepSize = math::Vector2f{ static_cast<float>(params.text.size()), 1.0f };
		params.size = (sizePerLetter * stepSize);
		params.border = math::Vector2f{ 20.0f, 4.0f };
		params.command = std::make_unique<cmnd::TestCommand>();
		entities.push_back(fact::ButtonFactory(params).create());
	}
	{
		auto params = app::par::ButtonFactoryParameters();
		params.position = math::Vector2f{ 300.0f, 80.0f };
		params.state = app::comp::Presseable::State::Active;
		params.text = std::string("Cancel");
		auto const & stepSize = math::Vector2f{ static_cast<float>(params.text.size()), 1.0f };
		params.size = (sizePerLetter * stepSize);
		params.border = math::Vector2f{ 20.0f, 4.0f };
		params.command = std::make_unique<cmnd::TestCommand>();
		entities.push_back(fact::ButtonFactory(params).create());
	}
	{
		auto const & size = math::Vector2f{ 1366.0f, 768.0f } / 3.0f;
		auto const & origin = size / 2.0f;
		auto const & position = math::Vector2f{ 0.0f, 0.0f };
		auto const & textureKey = app::res::TextureKey::Debug;
		auto const & zIndex = 1.9;
		entities.push_back(fact::BackgroundImageFactory(position, size, origin, textureKey, zIndex).create());
	}

	return entities;
}
