#include "stdafx.h"
#include "LobbySelectSceneFactory.h"
#include "factories/entities/CameraFactory.h"
#include "factories/entities/ImageFactory.h"
#include "factories/entities/ButtonFactory.h"

#include "commands/buttons/ButtonLobbySelectRefreshCommand.h"
#include "commands/TestCommand.h"

std::vector<app::Entity> app::fact::sce::LobbySelectSceneFactory::create()
{
	constexpr auto screenX = 1366.0f;
	constexpr auto screenY = 768.0f;
	constexpr auto halfScreenSizeX = screenX / 2.0f;
	constexpr auto halfScreenSizeY = screenY / 2.0f;
	constexpr auto fifthScreenX = screenX / 5.0f;
	constexpr auto fifthScreenY = screenY / 5.0f;
	auto entities = std::vector<app::Entity>();

	{
		auto const & size = math::Vector2f{ 1366.0f, 768.0f };
		auto const & origin = size / 2.0f;
		auto const & position = math::Vector2f{ 0.0f, 0.0f };
		auto const & textureKey = app::res::TextureKey::Debug;
		auto const & zIndex = 50u;
		entities.push_back(fact::ImageFactory(position, size, origin, textureKey, zIndex).create());
	}
	{
		auto const & sizePerLetter = math::Vector2f{ 20.0f, 40.0f };
		auto params = app::par::ButtonFactoryParameters();
		params.position = math::Vector2f{ 400.0f, -300.0f };
		params.state = app::comp::Widget::State::Highlighted;
		params.text = std::string("Refresh");
		auto const & stepSize = math::Vector2f{ static_cast<float>(params.text.size()), 1.0f };
		params.size = (sizePerLetter * stepSize);
		params.border = math::Vector2f{ 20.0f, 4.0f };
		params.entity = m_entityFactory.create();
		params.command = std::make_unique<cmnd::ButtonLobbySelectRefreshCommand>();
		params.zIndex = 80u;
		entities.push_back(fact::ButtonFactory(params).create());
	}

	entities.push_back(fact::CameraFactory().create());

	return entities;
}
