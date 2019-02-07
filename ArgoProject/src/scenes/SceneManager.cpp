#include "stdafx.h"
#include "SceneManager.h"

app::sce::SceneManager::SceneManager()
	: m_scenes(util::make_unordered_map<SceneType, Scene>({
		  std::make_pair(SceneType::CharacterSelect, Scene(std::in_place_type<sce::CharacterSelectScene>, m_targetScene))
		, std::make_pair(SceneType::Splash, Scene(std::in_place_type<sce::SplashScene>, m_targetScene))
	}))
	, m_currentScene(SceneType::Count)
	, m_targetScene(SceneType::Splash)
{
}

app::sce::SceneManager::~SceneManager()
{
	m_scenes.clear();
}

void app::sce::SceneManager::update(app::time::seconds const & dt)
{
	if (m_currentScene != m_targetScene) { this->changeScene(); }
	if constexpr (DEBUG_MODE) { assert(m_scenes.find(m_currentScene) != m_scenes.end()); }
	std::visit([&dt](auto & scene) { scene.update(dt); }, m_scenes.at(m_currentScene));
}

void app::sce::SceneManager::render(app::time::seconds const & dt)
{
	if constexpr (DEBUG_MODE) { assert(m_scenes.find(m_currentScene) != m_scenes.end()); }
	std::visit([&dt](auto & scene) { scene.render(dt); }, m_scenes.at(m_currentScene));
}

void app::sce::SceneManager::changeScene()
{
	if (m_currentScene == SceneType::Count)
	{
		// Setting scene for the first time
		if constexpr (DEBUG_MODE) { assert(m_scenes.find(m_targetScene) != m_scenes.end()); }
	}
	else
	{
		if constexpr (DEBUG_MODE) { assert(m_scenes.find(m_currentScene) != m_scenes.end() && m_scenes.find(m_targetScene) != m_scenes.end()); }
		std::visit([](auto & scene) { scene.end(); }, m_scenes.at(m_currentScene));
	}
	m_currentScene = m_targetScene;
	std::visit([](auto & scene) { scene.start(); }, m_scenes.at(m_currentScene));

}
