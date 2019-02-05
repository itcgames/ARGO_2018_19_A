#ifndef _AIR_MOTION_SYSTEM_H
#define _AIR_MOTION_SYSTEM_H

#include "BaseSystem.h"

namespace app::sys
{
	class AirMotionSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		AirMotionSystem() = default;
		virtual ~AirMotionSystem() = default;

		AirMotionSystem(AirMotionSystem const &) = default;
		AirMotionSystem & operator=(AirMotionSystem const &) = default;

		AirMotionSystem(AirMotionSystem &&) = default;
		AirMotionSystem & operator=(AirMotionSystem &&) = default;


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

#endif // !_AIR_MOTION_SYSTEM_H
