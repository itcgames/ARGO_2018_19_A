#include "stdafx.h"
#include "LobbySelectSceneFactory.h"
#include "factories/entities/CameraFactory.h"
#include "factories/entities/ImageFactory.h"
#include "factories/entities/ButtonFactory.h"

#include "commands/buttons/ButtonLobbySelectRefreshCommand.h"
#include "commands/buttons/ButtonLobbySelectCreateLobbyCommand.h"
#include "commands/TestCommand.h"

app::fact::sce::LobbySelectSceneFactory::LobbySelectSceneFactory(app::sce::SceneType & sceneControl)
	: SceneFactory()
	, m_sceneControl(sceneControl)
{
}

std::vector<app::Entity> app::fact::sce::LobbySelectSceneFactory::create()
{
	auto const & sizePerLetter = math::Vector2f{ 20.0f, 40.0f };
	auto entities = std::vector<app::Entity>();
	auto params = app::par::ButtonFactoryParameters();

	{
		auto const & size = math::Vector2f{ 1366.0f, 768.0f };
		auto const & origin = size / 2.0f;
		auto const & position = math::Vector2f{ 0.0f, 0.0f };
		auto const & textureKey = app::res::TextureKey::Debug;
		auto const & zIndex = 50u;
		entities.push_back(fact::ImageFactory(position, size, origin, textureKey, zIndex).create());
	}
	{
		params.entity = m_entityFactory.create();
		params.left.reset();
		params.right.reset();
		params.up.reset();
		params.down = m_entityFactory.create();
		params.position = math::Vector2f{ 400.0f, -300.0f };
		params.state = app::comp::Widget::State::Highlighted;
		params.text = std::string("Refresh");
		auto const & stepSize = math::Vector2f{ static_cast<float>(params.text.size()), 1.0f };
		params.size = (sizePerLetter * stepSize);
		params.border = math::Vector2f{ 20.0f, 4.0f };
		auto refreshCommandEntities = std::forward_list<app::Entity>();
		refreshCommandEntities.push_front(params.entity.value());
		params.command = std::make_unique<cmnd::ButtonLobbySelectRefreshCommand>(refreshCommandEntities, m_sceneControl);
		params.zIndex = 80u;
		entities.push_back(fact::ButtonFactory(params).create());
	}
	{
		params.up = params.entity;
		params.entity = params.down;
		params.down.reset();
		params.left.reset();
		params.right.reset();
		params.position = math::Vector2f{ 400.0f, 300.0f };
		params.state = app::comp::Widget::State::Active;
		params.text = std::string("Create Lobby");
		auto const & stepSize = math::Vector2f{ static_cast<float>(params.text.size()), 1.0f };
		params.size = (sizePerLetter * stepSize);
		params.border = math::Vector2f{ 20.0f, 4.0f };
		params.command = std::make_unique<cmnd::ButtonLobbySelectCreateLobbyCommand>("Bob", m_sceneControl);
		params.zIndex = 80u;
		entities.push_back(fact::ButtonFactory(params).create());
	}

	entities.push_back(fact::CameraFactory().create());

	return entities;
}
