#include "stdafx.h"
#include "BaseScene.h"
#include "singletons/RegistrySingleton.h"
#include "singletons/ResourceManagerSingleton.h"
#include "components/Layer.h"

app::sce::BaseScene::BaseScene(app::sce::SceneType & sceneManagerType, UpdateSystems && updateSystems, DrawSystems && drawSystems)
	: m_registry(app::sin::Registry::get())
	, m_sceneManagerType(sceneManagerType)
	, m_resourceManager(app::sin::ResourceManager::get())
	, m_updateSystems(std::make_move_iterator(updateSystems.begin()), std::make_move_iterator(updateSystems.end()))
	, m_drawSystems(std::make_move_iterator(drawSystems.begin()), std::make_move_iterator(drawSystems.end()))
{
}

app::sce::BaseScene::~BaseScene()
{
}

void app::sce::BaseScene::update(app::time::seconds const & dt)
{
	for (auto & variantSystem : m_updateSystems) { std::visit([&dt](auto & system) { system.update(dt); }, variantSystem); }
}

void app::sce::BaseScene::render(app::time::seconds const & dt)
{
	for (auto & variantSystem : m_drawSystems) { std::visit([&dt](auto & system) { system.update(dt); }, variantSystem); }
}

std::vector<app::Entity> app::sce::BaseScene::createEntities(fact::sce::SceneFactory & scenesFactory)
{
	m_registry.construction<comp::Layer>().disconnect<&app::sys::RenderSystem::onLayerConstruction>();
	auto && entities = scenesFactory.create();
	app::sys::RenderSystem::onLayerConstruction(m_registry, 0);
	m_registry.construction<comp::Layer>().connect<&app::sys::RenderSystem::onLayerConstruction>();
	return entities;
}
