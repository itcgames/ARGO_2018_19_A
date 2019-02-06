#include "stdafx.h"
#include "BaseScene.h"
#include "singletons/RegistrySingleton.h"

app::sce::BaseScene::BaseScene(app::sce::SceneType const & type, UpdateSystems && updateSystems, DrawSystems && drawSystems)
	: m_registry(app::sin::Registry::get())
	, m_type(type)
	, m_updateSystems(updateSystems)
	, m_drawSystems(drawSystems)
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
