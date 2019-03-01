#include "stdafx.h"
#include "SplashSceneFactory.h"
#include "factories/entities/CameraFactory.h"
#include "factories/entities/AnimatedImageFactory.h"
#include "parameters/AnimatedImageFactoryParameters.h"

std::vector<app::Entity> app::fact::sce::SplashSceneFactory::create()
{
	auto entities = std::vector<app::Entity>();
	entities.push_back(fact::CameraFactory().create());
	auto params = app::par::AnimatedImageFactoryParameters(); 
	{
		params.size = math::Vector2f{ 1366.0f, 768.0f };
		params.origin = params.size / 2.0f;
		params.position = math::Vector2f{ 0.0f, 0.0f };
		params.textureKey = app::res::TextureKey::Splash;
		params.zIndex = 50u;
		params.frameSize = math::Vector2f(200, 150);
		params.frameNumber = math::Vector2f(4, 0);
		params.animationLoop = false;
		params.maxFrames = 3;
		entities.push_back(fact::AnimatedImageFactory(params).create());
	}

	return entities;
}
