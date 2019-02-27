#include "stdafx.h"
#include "SceneManager.h"

app::sce::SceneManager::SceneManager(bool & gameRunning)
	: m_scenes(util::make_unordered_map<SceneType, Scene>({
		  std::make_pair(SceneType::Splash, Scene(std::in_place_type<sce::SplashScene>, m_targetScene))
		, std::make_pair(SceneType::CharacterSelect, Scene(std::in_place_type<sce::CharacterSelectScene>, m_targetScene))
		, std::make_pair(SceneType::Credits, Scene(std::in_place_type<sce::CreditsScene>, m_targetScene))
		, std::make_pair(SceneType::Level, Scene(std::in_place_type<sce::LevelScene>, m_targetScene))
		, std::make_pair(SceneType::LevelSelect, Scene(std::in_place_type<sce::LevelSelectScene>, m_targetScene))
		, std::make_pair(SceneType::Lobby, Scene(std::in_place_type<sce::LobbyScene>, m_targetScene))
		, std::make_pair(SceneType::LobbySelect, Scene(std::in_place_type<sce::LobbySelectScene>, m_targetScene))
		, std::make_pair(SceneType::MainMenu, Scene(std::in_place_type<sce::MainMenuScene>, m_targetScene))
		, std::make_pair(SceneType::MultiplayerLevel, Scene(std::in_place_type<sce::MultiplayerLevelScene>, m_targetScene))
		, std::make_pair(SceneType::TutorialLevel, Scene(std::in_place_type<sce::TutorialLevelScene>, m_targetScene))
		, std::make_pair(SceneType::Loading, Scene(std::in_place_type<sce::LoadingScene>, m_targetScene))
	}))
	, m_currentScene(SceneType::Count)
	, m_targetScene(SceneType::Level)
	, m_gameRunning(gameRunning)
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
	if (m_targetScene == SceneType::Exit) { m_gameRunning = false; return; }
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
