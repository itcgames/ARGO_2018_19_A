#ifndef _APP_GAME_H
#define _APP_GAME_H

#include "graphics/Window.h"

// systems
#include "systems/MotionSystem.h"
#include "systems/RenderSystem.h"

namespace app
{
	class Game
	{
	private: // Private typedefs/Enums/Usings
		using UpdateSystem = std::variant<sys::MotionSystem>;
		using UpdateSystems = std::array<UpdateSystem, 1>;
		using DrawSystem = std::variant<sys::RenderSystem>;
		using DrawSystems = std::array<DrawSystem, 1>;
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
		app::inp::ControllerHandler m_controllerHandler;
		app::inp::KeyHandler m_keyHandler;
		app::inp::MouseHandler m_mouseHandler;
		app::gra::Window m_window;
		app::Registry & m_registry;
		UpdateSystems m_updateSystems;
		DrawSystems m_drawSystems;
	};
}

#endif // !_APP_GAME_H
