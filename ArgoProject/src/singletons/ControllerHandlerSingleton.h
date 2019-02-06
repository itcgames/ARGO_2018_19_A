#ifndef _CONTROLLER_HANDLER_SINGLETON_H
#define _CONTROLLER_HANDLER_SINGLETON_H

namespace app::sin
{
	class ControllerHandler
	{
	public: // Constructors/Destructor/Assignments
		ControllerHandler() = default;
		~ControllerHandler() = default;

		ControllerHandler(ControllerHandler const &) = default;
		ControllerHandler & operator=(ControllerHandler const &) = default;

		ControllerHandler(ControllerHandler &&) = default;
		ControllerHandler & operator=(ControllerHandler &&) = default;

	public: // Public Static Functions
		static app::inp::ControllerHandler & get();
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
		static std::unique_ptr<app::inp::ControllerHandler> s_controllerHandler;
	private: // Private Member Variables
	};
}

#endif // !_CONTROLLER_HANDLER_SINGLETON_H
