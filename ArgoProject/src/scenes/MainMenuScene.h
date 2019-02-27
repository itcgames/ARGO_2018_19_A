#ifndef _MAIN_MENU_SCENE_H
#define _MAIN_MENU_SCENE_H

#include "BaseScene.h"
#include "network/Client.h"

#include "factories/entities/LevelDemoFactory.h"

namespace app::sce
{
	class MainMenuScene : public BaseScene
	{
	public: // Constructors/Destructor/Assignments
		MainMenuScene(SceneType & sceneManagerType);
		virtual ~MainMenuScene() = default;

		MainMenuScene(MainMenuScene const &) = default;
		MainMenuScene & operator=(MainMenuScene const &) = default;

		MainMenuScene(MainMenuScene &&) = default;
		MainMenuScene & operator=(MainMenuScene &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual void start() final override;
		virtual void end() final override;
		void startDemo(app::Registry & registry, app::Entity inputEntity);
		void reset(app::Registry & registry, app::Entity inputEntity);
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
		std::optional<fact::LevelDemoFactory> m_demoFactory;
		std::vector<std::uint32_t> m_demoEntities;
		bool resetDemo = true;
	};
}

#endif // !_MAIN_MENU_SCENE_H
