#ifndef _WINDOW_SINGLETON_H
#define _WINDOW_SINGLETON_H

#include "graphics/Window.h"

namespace app::sin
{
	class Window
	{
	private: // Constructors/Destructor/Assignments
		Window() = default;
		~Window() = default;

		Window(Window const &) = default;
		Window & operator=(Window const &) = default;

		Window(Window &&) = default;
		Window & operator=(Window &&) = default;

	public: // Public Static Functions
		static gra::Window & get();
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
		static std::unique_ptr<gra::Window> s_window;
	private: // Private Member Variables
	};
}

#endif // !_WINDOW_SINGLETON_H
