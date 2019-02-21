#include "stdafx.h"
#include "LobbyDisplayFactory.h"
#include "factories/entities/ImageFactory.h"
#include "factories/entities/TextFactory.h"

app::fact::LobbyDisplayFactory::LobbyDisplayFactory(
	  math::Vector2f const & position
	, std::string const & lobbyName
)
	: EntitiesFactory()
	, m_position(position)
	, m_lobbyName(lobbyName)
{
}

std::vector<app::Entity> app::fact::LobbyDisplayFactory::create()
{
	auto entities = std::vector<app::Entity>();
	auto const & startPosition = m_position;
	auto position = math::Vector2f{};
	auto size = math::Vector2f{};

	// Reserved for later being a icon
	{
		position = startPosition + math::Vector2f{ 10.0f, 0.0f};
		size = math::Vector2f{ 50.0f, 50.0f };
		auto const & origin = size / 2.0f;
		auto const & textureKey = app::res::TextureKey::Debug;
		auto const & zIndex = 110u;
		entities.push_back(fact::ImageFactory(position, size, origin, textureKey, zIndex).create());
	}
	// Text
	{
		position += size + math::Vector2f{ 10.0f, 0.0f };
		auto const & sizePerLetter = math::Vector2f{ 20.0f, 40.0f };
		auto const & text = m_lobbyName;
		auto const & stepSize = math::Vector2f{ static_cast<float>(text.size()), 1.0f };
		size = sizePerLetter * stepSize;
		entities.push_back(fact::TextFactory(position, size, text).create());
	}

	return entities;
}
