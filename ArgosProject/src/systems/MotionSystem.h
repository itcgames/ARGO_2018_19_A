#ifndef _SYSTEM_MOTION_H
#define _SYSTEM_MOTION_H

#include "BaseSystem.h"

namespace app::sys
{
	class MotionSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		MotionSystem() = default;
		~MotionSystem() = default;

		MotionSystem(MotionSystem const &) = default;
		MotionSystem(MotionSystem &&) = default;

		MotionSystem & operator=(MotionSystem const &) = default;
		MotionSystem & operator=(MotionSystem &&) = default;

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

#endif // !_SYSTEM_MOTION_H
