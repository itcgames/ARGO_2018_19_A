#include "stdafx.h"
#include "AskNameFactory.h"
#include "commands/TestCommand.h"
#include "commands/buttons/ButtonMainMenuMultiplayerConnectCancelCommand.h"
#include "commands/buttons/ButtonMainMenuMultiplayerConnectConfirmCommand.h"
#include "parameters/ButtonFactoryParameters.h"
#include "factories/entities/ButtonFactory.h"
#include "factories/entities/ImageFactory.h"

app::fact::mod::AskNameFactory::AskNameFactory(
	  app::Entity const callingEntity
	, app::sce::SceneType & sceneManagerControl
)
	: EntitiesFactory()
	, m_callingEntity(callingEntity)
	, m_sceneManagerControl(sceneManagerControl)
{
}

std::vector<app::Entity> app::fact::mod::AskNameFactory::create()
{
	constexpr auto DEFAULT_NAME = "Bob";
	auto entities = std::vector<app::Entity>();

	// Set widget navigation.

	{
		auto const & size = math::Vector2f{ 1366.0f, 768.0f } / 3.0f;
		auto const & origin = size / 2.0f;
		auto const & position = math::Vector2f{ 0.0f, 0.0f };
		auto const & textureKey = app::res::TextureKey::Debug;
		auto const & zIndex = 200u;
		entities.push_back(fact::ImageFactory(position, size, origin, textureKey, zIndex).create());
	}

	// Button creation
	{
		auto params = app::par::ButtonFactoryParameters();
		auto buttonFactory = fact::ButtonFactory(params);
		auto cancelCommand = std::make_shared<cmnd::ButtonMainMenuMultiplayerConnectCancelCommand>(m_callingEntity);
		auto confirmCommand = std::make_shared<cmnd::ButtonMainMenuMultiplayerConnectConfirmCommand>(m_callingEntity, DEFAULT_NAME, m_sceneManagerControl);
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
			params.command = confirmCommand;
			params.zIndex = 220u;
			entities.push_back(buttonFactory.create());
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
			params.command = cancelCommand;
			params.zIndex = 220u;
			entities.push_back(buttonFactory.create());
		}
		cancelCommand->setEntites(entities);
	}

	return entities;
}
