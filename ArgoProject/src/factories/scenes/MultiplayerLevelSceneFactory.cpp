#include "stdafx.h"
#include "MultiplayerLevelSceneFactory.h"
#include "factories/entities/PlayerFactory.h"
#include "factories/entities/CameraFactory.h"
#include "factories/LevelFactory.h"
#include "factories/GhostPlayerFactory.h"
#include "parameters/GhostPlayerFactoryParameters.h"
#include "tags/LobbyTag.h"

std::vector<app::Entity> app::fact::sce::MultiplayerLevelSceneFactory::create()
{
	auto position = math::Vector2f(0, 0);
	auto size = math::Vector2f(0, 0);

	auto entities = std::vector<app::Entity>();
	entities.reserve(50);

	auto player = fact::PlayerFactory().create();
	entities.push_back(player);

	auto level = fact::LevelFactory().create();	
	entities.insert(entities.end(), level.begin(), level.end());

	//GHOST PLAYERS
	auto params = app::par::GhostPlayerFactoryParameters();
	auto const & lobbyTag = m_registry.get<tag::Lobby>();
	auto const & [currentPlayerId, currentPlayerName] = lobbyTag.players.at(lobbyTag.playerIndex).value();
	for (auto const & player : lobbyTag.players)
	{
		if (!player.has_value() || player->first == currentPlayerId) { continue; }

		auto const &[id, name] = player.value();

		params.position = math::Vector2f(900, 100);
		params.id = id;
		entities.push_back(fact::GhostPlayerFactory(params).create());
	}

	auto cameraParams = app::par::CameraParameters();
	cameraParams.targetEntity = player;
	cameraParams.clampRect = math::Rectf({ -800.0f, 300.0f }, { 2000.0f, 1000.0f });
	cameraParams.internalClamp = math::Vector2f(20.0f, 60.0f);
	entities.push_back(fact::CameraFactory(std::move(cameraParams)).create());

	return entities;
}
