#ifndef _SYSTEM_CAMERA
#define _SYSTEM_CAMERA

#include "BaseSystem.h"

namespace app::sys
{
	class CameraSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		CameraSystem();
		~CameraSystem() = default;

		CameraSystem(CameraSystem const &) = default;
		CameraSystem(CameraSystem &&) = default;

		CameraSystem & operator=(CameraSystem const &) = default;
		CameraSystem & operator=(CameraSystem &&) = default;

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

#endif // !_SYSTEM_CAMERA
