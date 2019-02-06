#include "stdafx.h"
#include "SplashSceneFactory.h"
#include "singletons/WindowSingleton.h"
#include "factories/PlayerFactory.h"

app::fact::sce::SplashSceneFactory::SplashSceneFactory()
	: EntitiesFactory()
	, m_renderer(app::sin::Window::get().getRenderer())
{
}

std::vector<app::Entity> app::fact::sce::SplashSceneFactory::create()
{
	auto entities = std::vector<app::Entity>();

	entities.push_back(fact::PlayerFactory(m_renderer).create());

	return entities;
}
