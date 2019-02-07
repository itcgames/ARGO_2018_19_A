#ifndef _DASH_SYSTEM_H
#define _DASH_SYSTEM_H

#include "BaseSystem.h"

namespace app::sys
{
	class DashSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		DashSystem() = default;
		virtual ~DashSystem() = default;

		DashSystem(DashSystem const &) = default;
		DashSystem & operator=(DashSystem const &) = default;

		DashSystem(DashSystem &&) = default;
		DashSystem & operator=(DashSystem &&) = default;


	public: // Public Static Functions
	public: // Public Member Functions
		virtual void update(app::time::seconds const & dt) override;
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

#endif // !_DASH_SYSTEM_H
