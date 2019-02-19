#include "stdafx.h"
#include "AskNameFactory.h"
#include "commands/TestCommand.h"
#include "commands/buttons/ButtonMultiplayerCancelCommand.h"
#include "parameters/ButtonFactoryParameters.h"
#include "factories/entities/ButtonFactory.h"
#include "factories/entities/BackgroundImageFactory.h"

app::fact::mod::AskNameFactory::AskNameFactory(app::Entity const & callingEntity)
	: EntitiesFactory()
	, m_callingEntity(callingEntity)
{
}

std::vector<app::Entity> app::fact::mod::AskNameFactory::create()
{
	auto entities = std::vector<app::Entity>();

	// Set widget navigation.
	auto params = app::par::ButtonFactoryParameters();
	auto cancelCommand = std::make_shared<cmnd::ButtonMultiplayerCancelCommand>(m_callingEntity);

	auto const & sizePerLetter = math::Vector2f{ 20.0f, 40.0f };
	{
		params.left.reset();
		params.up.reset();
		params.down.reset();
		params.entity = m_entityFactory.create();
		params.right = m_entityFactory.create();
		params.position = math::Vector2f{ -100.0f, 80.0f };
		params.state = app::comp::Widget::State::Highlighted;
		params.text = std::string("Confirm");
		auto const & stepSize = math::Vector2f{ static_cast<float>(params.text.size()), 1.0f };
		params.size = (sizePerLetter * stepSize);
		params.border = math::Vector2f{ 20.0f, 4.0f };
		params.command = cancelCommand;
		entities.push_back(fact::ButtonFactory(params).create());
	}
	{
		params.left = params.entity;
		params.entity = params.right;
		params.right.reset();
		params.up.reset();
		params.down.reset();
		params.position = math::Vector2f{ 100.0f, 80.0f };
		params.state = app::comp::Widget::State::Active;
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
		auto const & zIndex = 1.0;
		entities.push_back(fact::BackgroundImageFactory(position, size, origin, textureKey, zIndex).create());
	}

	cancelCommand->setEntites(entities);
	return entities;
}
