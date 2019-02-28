#ifndef _WIDGET_NAVIGATION_SYSTEM_H
#define _WIDGET_NAVIGATION_SYSTEM_H

#include "BaseSystem.h"

namespace app::sys
{
	class WidgetNavigationSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		WidgetNavigationSystem();
		virtual ~WidgetNavigationSystem() = default;

		WidgetNavigationSystem(WidgetNavigationSystem const &) = default;
		WidgetNavigationSystem & operator=(WidgetNavigationSystem const &) = default;

		WidgetNavigationSystem(WidgetNavigationSystem &&) = default;
		WidgetNavigationSystem & operator=(WidgetNavigationSystem &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual void update(app::time::seconds const & dt) final override;
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
		bool isAxisOver(std::initializer_list<app::inp::ControllerAxisCode> const &, double const &);
	private: // Private Static Variables
		constexpr static bool s_DEBUG_MODE = true;
		constexpr static double s_THRESHOLD = 0.6;
	private: // Private Member Variables
		app::inp::KeyHandler & m_keyHandler;
		app::inp::ControllerHandler & m_controllerHandler;
	};
}

#endif // !_WIDGET_NAVIGATION_SYSTEM_H
