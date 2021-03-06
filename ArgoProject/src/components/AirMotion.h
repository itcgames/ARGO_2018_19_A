﻿#ifndef _COMP_AIR_MOTION_H
#define _COMP_AIR_MOTION_H

namespace app::comp
{
	struct AirMotion
	{
	public: // Constructors/Destructor/Assignments
		AirMotion() = default;
		~AirMotion() = default;

		AirMotion(AirMotion const &) = default;
		AirMotion & operator=(AirMotion const &) = default;

		AirMotion(AirMotion &&) = default;
		AirMotion & operator=(AirMotion &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
		constexpr static float DEFAULT_MAX_SPEED = 500.0f;
	public: // Public Member Variables
		math::Vector2f gravity = { 0.0f, 9.8f};
		float speed = 0.0f;
		float angularSpeed = 0.0f;
		float direction = 0.0f;
		float lateralConstraint = 0.2f;
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

#endif // !_COMP_AIR_MOTION_H
