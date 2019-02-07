#ifndef _MOUSE_HANDLER_SINGLETON_H
#define _MOUSE_HANDLER_SINGLETON_H

namespace app::sin
{
	class MouseHandler
	{
	public: // Constructors/Destructor/Assignments
		MouseHandler() = default;
		~MouseHandler() = default;

		MouseHandler(MouseHandler const &) = default;
		MouseHandler & operator=(MouseHandler const &) = default;

		MouseHandler(MouseHandler &&) = default;
		MouseHandler & operator=(MouseHandler &&) = default;

	public: // Public Static Functions
		static app::inp::MouseHandler & get();
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
		static std::unique_ptr<app::inp::MouseHandler> s_mouseHandler;
	private: // Private Member Variables
	};
}

#endif // !_MOUSE_HANDLER_SINGLETON_H
