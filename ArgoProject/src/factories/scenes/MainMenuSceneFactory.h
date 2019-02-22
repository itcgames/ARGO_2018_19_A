#ifndef _FACTORY_MAIN_MENU_SCENE_H
#define _FACTORY_MAIN_MENU_SCENE_H

#include "../SceneFactory.h"

namespace app::fact::sce
{
	class MainMenuSceneFactory : public SceneFactory
	{
	public: // Constructors/Destructor/Assignments
		MainMenuSceneFactory() = default;
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
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_FACTORY_MAIN_MENU_SCENE_H
