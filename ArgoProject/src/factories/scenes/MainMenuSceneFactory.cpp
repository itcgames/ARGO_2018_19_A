#include "stdafx.h"
#include "MainMenuSceneFactory.h"
#include "factories/entities/CameraFactory.h"
#include "factories/entities/ImageFactory.h"
#include "factories/entities/ButtonFactory.h"
#include "factories/entities/TextFactory.h"
#include "factories/entities/PlayerFactory.h"
#include "factories/AIFactory.h"
#include "factories/LevelFactory.h"

#include "commands/buttons/ButtonMainMenuMultiplayerConnectCommand.h"
#include "network/Client.h"

app::fact::sce::MainMenuSceneFactory::MainMenuSceneFactory(app::sce::SceneType & targetScene)
	: m_targetScene(targetScene)
{
}

std::vector<app::Entity> app::fact::sce::MainMenuSceneFactory::create()
{
	m_audioPlayer.playAudioMusic(app::res::AudioKey::BackgroundMusicTitle, app::gra::AudioPlayer::s_LOOP_FOREVER);
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
		auto const & zIndex = 50u;
		entities.push_back(fact::ImageFactory(position, size, origin, textureKey, zIndex).create());
	}
	{
		auto const & sizePerLetter = math::Vector2f{ 20.0f, 40.0f };
		auto params = app::par::ButtonFactoryParameters();
		params.position = math::Vector2f{ 0.0f, 0.0f };
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
		auto const & position = app::math::Vector2f(750, 200);
		auto const & sizePerLetter = math::Vector2f{ 20.0f, 40.0f };
		auto const & text = std::string("Are you not entertained!");
		auto const & stepSize = math::Vector2f{ static_cast<float>(text.size()), 1.0f };
		entities.push_back(fact::TextFactory(position, sizePerLetter * stepSize, text).create());
	}
	return entities;
}
