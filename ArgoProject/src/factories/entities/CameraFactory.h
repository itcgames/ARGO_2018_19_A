#ifndef _FACTORY_CAMERA_H
#define _FACTORY_CAMERA_H

#include "../EntityFactory.h"
#include "parameters/CameraParameters.h"

namespace app::fact
{
	class CameraFactory : public EntityFactory
	{
	public: // Constructors/Destructor/Assignments
		CameraFactory(app::par::CameraParameters param = app::par::CameraParameters());
		virtual ~CameraFactory() = default;

		CameraFactory(CameraFactory const &) = default;
		CameraFactory & operator=(CameraFactory const &) = default;

		CameraFactory(CameraFactory &&) = default;
		CameraFactory & operator=(CameraFactory &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual app::Entity const create() override;
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
		app::par::CameraParameters parameters;
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_FACTORY_CAMERA_H
