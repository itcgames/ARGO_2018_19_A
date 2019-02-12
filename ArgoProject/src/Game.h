#ifndef _APP_GAME_H
#define _APP_GAME_H

#include "graphics/Window.h"
#include "scenes/SceneManager.h"
#include "resources/ResourceManager.h"

namespace app
{
	class Game
	{
	public: // Constructors/Destructor/Assignments
		Game();
		~Game();

		Game(Game const &) = default;
		Game(Game &&) = default;

		Game & operator=(Game const &) = default;
		Game & operator=(Game &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		constexpr bool isRunning() { return m_running && m_window.isOpen(); }
		void pollEvents();
		void update(app::time::seconds const & dt);
		void render(app::time::seconds const & dt);
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
		bool m_running;
		app::inp::ControllerHandler & m_controllerHandler;
		app::inp::KeyHandler & m_keyHandler;
		app::inp::MouseHandler & m_mouseHandler;
		app::gra::Window & m_window;
		app::Registry & m_registry;
		app::res::ResourceManager<true> & m_resourceManager;
		app::sce::SceneManager m_sceneManager;
	};
}

#endif // !_APP_GAME_H
