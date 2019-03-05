#include "stdafx.h"
#include "LobbySceneFactory.h"
#include "factories/entities/CameraFactory.h"
#include "factories/entities/ButtonFactory.h"

#include "commands/buttons/ButtonLobbyReadyCommand.h"

app::fact::sce::LobbySceneFactory::LobbySceneFactory(app::sce::SceneType & sceneControl)
	: m_sceneControl(sceneControl)
{
}

std::vector<app::Entity> app::fact::sce::LobbySceneFactory::create()
{
	auto const & sizePerLetter = math::Vector2f{ 20.0f, 40.0f };
	auto entities = std::vector<app::Entity>();
	auto params = app::par::ButtonFactoryParameters();

	{
		params.entity = m_entityFactory.create();
		params.left.reset();
		params.right.reset();
		params.up.reset();
		params.down.reset();
		params.position = math::Vector2f{ 0.0f, 300.0f };
		params.state = app::comp::Widget::State::Highlighted;
		params.text = std::string("Ready");
		auto const & stepSize = math::Vector2f{ static_cast<float>(params.text.size()), 1.0f };
		params.size = (sizePerLetter * stepSize);
		params.border = math::Vector2f{ 20.0f, 4.0f };
		auto refreshCommandEntities = std::forward_list<app::Entity>();
		refreshCommandEntities.push_front(params.entity.value());
		params.command = std::make_unique<cmnd::ButtonLobbyReadyCommand>(refreshCommandEntities, m_sceneControl);
		params.zIndex = 80u;
		entities.push_back(fact::ButtonFactory(params).create());
	}
	entities.push_back(fact::CameraFactory().create());

	return entities;
}
