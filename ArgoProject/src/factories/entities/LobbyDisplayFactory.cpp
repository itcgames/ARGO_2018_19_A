#include "stdafx.h"
#include "LobbyDisplayFactory.h"

#include "factories/entities/ImageFactory.h"
#include "factories/entities/TextFactory.h"
#include "factories/entities/ButtonFactory.h"

#include "components/LobbyDisplay.h"
#include "components/Destroy.h"

#include "commands/buttons/ButtonLobbySelectCommand.h"

app::fact::LobbyDisplayFactory::LobbyDisplayFactory(app::par::LobbyDisplayFactoryParameters const & params, app::sce::SceneType & sceneControl)
	: EntitiesFactory()
	, m_params(params)
	, m_sceneControl(sceneControl)
{
}

std::vector<app::Entity> app::fact::LobbyDisplayFactory::create()
{
	constexpr auto IS_NOT_HOST = false;
	auto entities = std::vector<app::Entity>();
	auto const & START_POSITION = m_params.position;
	auto const & DOWNWARD_OFFSET = math::Vector2f{ 0.0f, 50.0f };
	auto const & SIZE_PER_LETTER = math::Vector2f{ 20.0f, 40.0f };
	auto const & MAX_LOBBY_NAME_SIZE = math::Vector2f{ 200.0f, SIZE_PER_LETTER.y };
	auto const & IGNORE_Y = math::Vector2f{ 1.0f, 0.0f };
	auto position = math::Vector2f{};
	auto size = math::Vector2f{};
	auto offsetFromPrevious = math::Vector2f{};
	auto params = par::ButtonFactoryParameters();
	bool firstButton = true;

	// get rid of previous lobby displays
	{
		auto lobbyDisplayView = m_registry.view<comp::LobbyDisplay>();
		for (auto const & entity : lobbyDisplayView)
		{
			m_registry.destroy(entity);
		}
	}

	position = START_POSITION;
	for (auto const & lobby : m_params.lobbies)
	{
		auto const & lobbyName = lobby.getName();
		auto const & players = lobby.getPlayers();
		auto const PREVIOUS_POSITION = position;

		// Button
		{
			params.up = params.entity;
			params.entity = params.down;
			params.down = m_entityFactory.create();
			params.left.reset();
			params.right = m_params.entities.back();
			params.position = 
				position = PREVIOUS_POSITION + math::Vector2f{ -70.0f, 0.0f };
			params.size = 
				size = math::Vector2f{ 50.0f, 50.0f };
			params.state = app::comp::Widget::State::Active;
			params.zIndex = 140u;
			params.command = std::make_unique<cmnd::ButtonLobbySelectCommand>(lobby, IS_NOT_HOST, m_sceneControl);
			params.text = " ";

			entities.push_back(fact::ButtonFactory(params).create());

			// need to set the refresh button navigation
			if (firstButton)
			{
				firstButton = false;
				auto widgetView = m_registry.view<comp::Widget>();
				auto destroyView = m_registry.view<comp::Widget, comp::Destroy>();
				for (auto const & entity : m_params.entities)
				{
					if (widgetView.contains(entity) && !destroyView.contains(entity) && (entity != entities.back()))
					{
						auto & widget = widgetView.get(entity);
						widget.left = entities.back();
					}
				}
			}

			offsetFromPrevious = size / 2.0f;
		}
		// Reserved for later being a icon
		{
			position += ((size + offsetFromPrevious) * IGNORE_Y) + math::Vector2f{ 10.0f, 0.0f };
			size = math::Vector2f{ 50.0f, 50.0f };
			auto const & origin = size / 2.0f;
			auto const & textureKey = app::res::TextureKey::DebugAnimation;
			auto const & zIndex = 110u;
			entities.push_back(fact::ImageFactory(position, size, origin, textureKey, zIndex).create());
			offsetFromPrevious = size / 2.0f;
		}
		// Text
		{
			auto const & text = lobbyName;
			auto const & stepSize = math::Vector2f{ static_cast<float>(text.size()), 1.0f };
			size = std::min(SIZE_PER_LETTER * stepSize, MAX_LOBBY_NAME_SIZE,
				[](math::Vector2f const & lhs, math::Vector2f const & rhs) { return lhs.magnitudeSqr() < rhs.magnitudeSqr(); });
			position += ((size + offsetFromPrevious) * IGNORE_Y) + math::Vector2f{ 20.0f, 0.0f };
			entities.push_back(fact::TextFactory(position, size, text).create());
			offsetFromPrevious = size / 2.0f;
		}
		{
			auto const & text = (std::stringstream() << "Players " << this->getNumberOfPlayersIn(lobby) << "/4").str();
			auto const & stepSize = math::Vector2f{ static_cast<float>(text.size()), 1.0f };
			size = SIZE_PER_LETTER * stepSize;
			position += ((size + offsetFromPrevious) * IGNORE_Y) + math::Vector2f{ 10.0f, 0.0f };
			entities.push_back(fact::TextFactory(position, size, text).create());
			offsetFromPrevious = size / 2.0f;
		}

		position = PREVIOUS_POSITION + DOWNWARD_OFFSET;
	}

	// Add lobby display component to all entities that belong to the lobby display.
	for (auto const & entity : entities) { m_registry.assign<comp::LobbyDisplay>(entity); }

	return entities;
}

std::size_t app::fact::LobbyDisplayFactory::getNumberOfPlayersIn(app::net::Lobby const & lobby) const
{
	auto const & players = lobby.getPlayers();
	auto const predicate = [](app::net::Lobby::Player const & player) { return player.has_value(); };
	return std::count_if(players.begin(), players.end(), predicate);
}
