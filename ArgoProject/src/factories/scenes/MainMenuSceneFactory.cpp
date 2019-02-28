﻿#include "stdafx.h"
#include "MainMenuSceneFactory.h"
#include "network/Client.h"

#include "factories/entities/CameraFactory.h"
#include "factories/entities/ImageFactory.h"
#include "factories/entities/ButtonFactory.h"
#include "factories/entities/TextFactory.h"
#include "factories/entities/PlayerFactory.h"
#include "factories/AIFactory.h"
#include "factories/LevelFactory.h"

#include "components/Destroy.h"
#include "components/Background.h"

#include "commands/buttons/ButtonMainMenuSinglePlayerCommand.h"
#include "commands/buttons/ButtonMainMenuMultiplayerConnectCommand.h"
#include "commands/buttons/ButtonMainMenuCreditsCommand.h"
#include "commands/buttons/ButtonMainMenuExitCommand.h"

#include "tags/DynamicNodes.h"

app::fact::sce::MainMenuSceneFactory::MainMenuSceneFactory(app::sce::SceneType & targetScene, std::optional<app::fact::LevelDemoFactory> & levelFactory)
	: SceneFactory()
	, m_targetScene(targetScene)
	, m_levelFactory(levelFactory)
{
}

std::vector<app::Entity> app::fact::sce::MainMenuSceneFactory::create()
{
	m_audioPlayer.playAudioMusic(app::res::AudioKey::BackgroundMusicTitle, app::gra::AudioPlayer::s_LOOP_FOREVER);
	auto entities = std::vector<app::Entity>();
	auto cameraEntity = app::Entity();

	{
		auto const & size = math::Vector2f{ 1516.0f, 918.0f };
		auto const & origin = size / 2.0f;
		auto const & position = app::math::Vector2f(750, 200);
		auto const & textureKey = app::res::TextureKey::MainMenuBackground;
		auto const & zIndex = 50u;
		auto background = fact::ImageFactory(position, size, origin, textureKey, zIndex).create();
		auto destroy = comp::Destroy();
		destroy.timeToLive = 5.0f;
		m_registry.assign<decltype(destroy)>(background, std::move(destroy));
		m_registry.assign<comp::Background>(background);
		entities.push_back(background);

		auto cameraParams = app::par::CameraParameters();
		cameraParams.targetEntity = background;
		cameraEntity = fact::CameraFactory(std::move(cameraParams)).create();
		entities.push_back(cameraEntity);
		m_levelFactory.emplace(cameraEntity);
	}
	// Title
	{
		auto const & size = math::Vector2f{ 600.0f, 300.0f };
		auto const & origin = size / 2.0f;
		auto const & position = app::math::Vector2f(0, -250);
		auto const & textureKey = app::res::TextureKey::Title;
		auto const & zIndex = 200u;
		auto const & followEntity = cameraEntity;
		entities.push_back(fact::ImageFactory(position, size, origin, textureKey, zIndex, followEntity).create());
	}
	// Create all buttons
	{
		auto params = app::par::ButtonFactoryParameters();
		params.follow = cameraEntity;
		params.zIndex = 200u;
		{
			params.text = std::string("Singleplayer");
			auto const & sizePerLetter = math::Vector2f{ 20.0f, 40.0f };
			params.up.reset();
			params.entity = m_entityFactory.create();
			params.down = m_entityFactory.create();
			params.left.reset();
			params.right.reset();
			params.position = math::Vector2f{ 0.0f, -100.0f }; // offset from the cameras center
			params.state = app::comp::Widget::State::Highlighted;
			auto const & stepSize = math::Vector2f{ static_cast<float>(params.text.size()), 1.0f };
			params.size = (sizePerLetter * stepSize);
			params.border = math::Vector2f{ 20.0f, 4.0f };
			params.command = std::make_unique<cmnd::ButtonMainMenuSinglePlayerCommand>(m_targetScene);
			entities.push_back(fact::ButtonFactory(params).create());
		}
		{
			params.text = std::string("Multiplayer");
			auto const & sizePerLetter = math::Vector2f{ 20.0f, 40.0f };
			params.up = params.entity;
			params.entity = params.down;
			params.down = m_entityFactory.create();
			params.left.reset();
			params.right.reset();
			params.position = math::Vector2f{ 0.0f, 0.0f }; // offset from the cameras center
			params.state = app::comp::Widget::State::Active;
			auto const & stepSize = math::Vector2f{ static_cast<float>(params.text.size()), 1.0f };
			params.size = (sizePerLetter * stepSize);
			params.border = math::Vector2f{ 20.0f, 4.0f };
			params.command = std::make_unique<cmnd::ButtonMainMenuMultiplayerConnectCommand>(app::net::Client::s_SERVER_IP, app::net::Client::s_SERVER_PORT, params.entity.value(), cameraEntity, m_targetScene);
			entities.push_back(fact::ButtonFactory(params).create());
		}
		{
			params.text = std::string("Credits");
			auto const & sizePerLetter = math::Vector2f{ 20.0f, 40.0f };
			params.up = params.entity;
			params.entity = params.down;
			params.down = m_entityFactory.create();
			params.left.reset();
			params.right.reset();
			params.position = math::Vector2f{ 0.0f, 100.0f }; // offset from the cameras center
			params.state = app::comp::Widget::State::Active;
			auto const & stepSize = math::Vector2f{ static_cast<float>(params.text.size()), 1.0f };
			params.size = (sizePerLetter * stepSize);
			params.border = math::Vector2f{ 15.0f, 4.0f };
			params.command = std::make_unique<cmnd::ButtonMainMenuCreditsCommand>(m_targetScene);
			entities.push_back(fact::ButtonFactory(params).create());
		}
		{
			params.text = std::string("Exit");
			auto const & sizePerLetter = math::Vector2f{ 20.0f, 40.0f };
			params.up = params.entity;
			params.entity = params.down;
			params.down.reset();
			params.left.reset();
			params.right.reset();
			params.position = math::Vector2f{ 0.0f, 200.0f }; // offset from the cameras center
			params.state = app::comp::Widget::State::Active;
			auto const & stepSize = math::Vector2f{ static_cast<float>(params.text.size()), 1.0f };
			params.size = (sizePerLetter * stepSize);
			params.border = math::Vector2f{ 10.0f, 4.0f };
			params.command = std::make_unique<cmnd::ButtonMainMenuExitCommand>(m_targetScene);
			entities.push_back(fact::ButtonFactory(params).create());
		}
	}

	if (!m_registry.has<tag::DynamicNodes>()) { m_registry.assign<tag::DynamicNodes>(entt::tag_t(), m_registry.create()); }

	return entities;
}
