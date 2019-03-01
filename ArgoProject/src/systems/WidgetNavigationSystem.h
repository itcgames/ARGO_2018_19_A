#ifndef _WIDGET_NAVIGATION_SYSTEM_H
#define _WIDGET_NAVIGATION_SYSTEM_H

#include "BaseSystem.h"
#include "resources/ResourceManager.h"

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
	private: // Private Static Variables
		constexpr static bool s_DEBUG_MODE = true;
	private: // Private Member Variables
		app::inp::KeyHandler & m_keyHandler;
		app::res::ResourceManager<true> & m_resourceManager;
	};
}

#endif // !_WIDGET_NAVIGATION_SYSTEM_H
