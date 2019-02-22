#include "stdafx.h"
#include "MainMenuSceneFactory.h"
#include "factories/entities/CameraFactory.h"
#include "factories/entities/ImageFactory.h"
#include "factories/entities/ButtonFactory.h"
#include "factories/entities/TextFactory.h"
#include "factories/entities/PlayerFactory.h"
#include "factories/AIFactory.h"
#include "factories/LevelFactory.h"

#include "components/Destroy.h"

#include "commands/buttons/ButtonMainMenuMultiplayerConnectCommand.h"
#include "network/Client.h"

app::fact::sce::MainMenuSceneFactory::MainMenuSceneFactory(app::sce::SceneType & targetScene)
	: EntitiesFactory()
	, m_targetScene(targetScene)
{
}

std::vector<app::Entity> app::fact::sce::MainMenuSceneFactory::create()
{
	auto entities = std::vector<app::Entity>();


	{
		auto const & size = math::Vector2f{ 1366.0f, 768.0f };
		auto const & origin = size / 2.0f;
		auto const & position = app::math::Vector2f(750, 200);
		auto const & textureKey = app::res::TextureKey::Debug;
		auto const & zIndex = 50u;
		auto background = fact::ImageFactory(position, size, origin, textureKey, zIndex).create();
		auto destroy = comp::Destroy();
		destroy.timeToLive = 5.0f;
		m_registry.assign<decltype(destroy)>(background, std::move(destroy));
		entities.push_back(background);

		auto cameraParams = app::par::CameraParameters();
		cameraParams.targetEntity = background;
		entities.push_back(fact::CameraFactory(std::move(cameraParams)).create());
	}
	{
		auto const & sizePerLetter = math::Vector2f{ 20.0f, 40.0f };
		auto params = app::par::ButtonFactoryParameters();
		params.position = math::Vector2f{ 750.0f, 200.0f };
		params.state = app::comp::Widget::State::Highlighted;
		params.text = std::string("Multiplayer");
		auto const & stepSize = math::Vector2f{ static_cast<float>(params.text.size()), 1.0f };
		params.size = (sizePerLetter * stepSize);
		params.border = math::Vector2f{ 20.0f, 4.0f };
		params.entity = m_entityFactory.create();
		params.command = std::make_unique<cmnd::ButtonMainMenuMultiplayerConnectCommand>(app::net::Client::s_SERVER_IP, app::net::Client::s_SERVER_PORT, params.entity.value(), m_targetScene);
		params.zIndex = 80u;
		entities.push_back(fact::ButtonFactory(params).create());
	}
	{
		auto const & position = app::math::Vector2f(750, 100);
		auto const & sizePerLetter = math::Vector2f{ 20.0f, 40.0f };
		auto const & text = std::string("Are you not entertained!");
		auto const & stepSize = math::Vector2f{ static_cast<float>(text.size()), 1.0f };
		entities.push_back(fact::TextFactory(position, sizePerLetter * stepSize, text).create());
	}
	return entities;
}
