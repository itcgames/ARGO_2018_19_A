#include "stdafx.h"
#include "SplashSceneFactory.h"
#include "factories/entities/CameraFactory.h"
#include "factories/entities/BackgroundImageFactory.h"
#include "factories/entities/AnimatedImageFactory.h"

std::vector<app::Entity> app::fact::sce::SplashSceneFactory::create()
{
	auto entities = std::vector<app::Entity>();
	entities.push_back(fact::CameraFactory().create());

	{
		auto const & size = math::Vector2f{ 1366.0f, 768.0f };
		auto const & origin = size / 2.0f;
		auto const & position = math::Vector2f{ 0.0f, 0.0f };
		auto const & textureKey = app::res::TextureKey::Splash;
		entities.push_back(fact::AnimatedImageFactory(position, size, origin, textureKey, math::Vector2f(200,150), math::Vector2f(3,0)).create());
	}

	{
		auto const & size = math::Vector2f{ 1366.0f, 768.0f };
		auto const & origin = size / 2.0f;
		auto const & position = math::Vector2f{ 0.0f, 0.0f };
		auto const & textureKey = app::res::TextureKey::Loading;
		entities.push_back(fact::AnimatedImageFactory(position, size, origin, textureKey, math::Vector2f(200, 150), math::Vector2f(3, 0)).create());
	}

	return entities;
}
