#ifndef _BUTTON_SYSTEM_H
#define _BUTTON_SYSTEM_H

#include "BaseSystem.h"

namespace app::sys
{
	class ButtonSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		ButtonSystem();
		virtual ~ButtonSystem() = default;

		ButtonSystem(ButtonSystem const &) = default;
		ButtonSystem & operator=(ButtonSystem const &) = default;

		ButtonSystem(ButtonSystem &&) = default;
		ButtonSystem & operator=(ButtonSystem &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual void update(app::time::seconds const & dt) final override;
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
		app::inp::KeyHandler & m_keyHandler;
		app::inp::MouseHandler & m_mouseHandler;
		app::inp::ControllerHandler & m_controllerHandler;
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_BUTTON_SYSTEM_H
