#ifndef _FACTORY_MAIN_MENU_SCENE_H
#define _FACTORY_MAIN_MENU_SCENE_H

#include "../EntitiesFactory.h"
#include "scenes/SceneType.h"
#include "factories/entities/LevelDemoFactory.h"

namespace app::fact::sce
{
	class MainMenuSceneFactory : public EntitiesFactory
	{
	public: // Constructors/Destructor/Assignments
		MainMenuSceneFactory(app::sce::SceneType & targetScene, std::optional<app::fact::LevelDemoFactory> & levelFactory);
		virtual ~MainMenuSceneFactory() = default;

		MainMenuSceneFactory(MainMenuSceneFactory const &) = default;
		MainMenuSceneFactory & operator=(MainMenuSceneFactory const &) = default;

		MainMenuSceneFactory(MainMenuSceneFactory &&) = default;
		MainMenuSceneFactory & operator=(MainMenuSceneFactory &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual std::vector<app::Entity> create() final override;
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
		app::sce::SceneType & m_targetScene;
		std::optional<app::fact::LevelDemoFactory> & m_levelFactory;
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_FACTORY_MAIN_MENU_SCENE_H
