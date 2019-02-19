#ifndef _SYSTEM_HEALTH_H
#define _SYSTEM_HEALTH_H

#include "utilities/cute_c2.h"
#include "BaseSystem.h"

namespace app::sys
{
	class HealthSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		HealthSystem() = default;
		~HealthSystem() = default;

		HealthSystem(HealthSystem const &) = default;
		HealthSystem & operator=(HealthSystem const &) = default;

		HealthSystem(HealthSystem &&) = default;
		HealthSystem & operator=(HealthSystem &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual void update(app::time::seconds const & dt) override;
		void checkPlayerHealth(app::time::seconds const & dt);
		void checkDestructibleHealth(app::time::seconds const & dt);
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

#endif // !_SYSTEM_HEALTH_H
