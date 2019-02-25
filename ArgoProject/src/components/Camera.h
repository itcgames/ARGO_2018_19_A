#ifndef _CAMERA_H
#define _CAMERA_H

#include "math/Vector2.h"

namespace app::comp
{
	struct Camera
	{
	public: // Constructors/Destructor/Assignments
		Camera() = default;
		~Camera() = default;

		Camera(Camera const &) = default;
		Camera & operator=(Camera const &) = default;

		Camera(Camera &&) = default;
		Camera & operator=(Camera &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		math::Vector2f center;
		math::Vector2f size;
		std::optional<app::Entity> target;
		std::optional<math::Rectf> clampRect;
		std::optional<math::Vector2f> internalClamp;
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

#endif // !_CAMERA_H
