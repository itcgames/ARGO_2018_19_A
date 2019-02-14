#ifndef _COMPONENT_MOTION_H
#define _COMPONENT_MOTION_H

namespace app::comp
{
	struct Motion
	{
	public: // Constructors/Destructor/Assignments
		Motion() = default;
		~Motion() = default;

		Motion(Motion const &) = default;
		Motion(Motion &&) = default;

		Motion & operator=(Motion const &) = default;
		Motion & operator=(Motion &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
		constexpr static float DRAG = 0.95f;
		constexpr static float DRAG_CUTOFF = 20.0f;
		constexpr static float MAX_SPEED = 300.0f;
	public: // Public Member Variables
		float speed;
		float angularSpeed;
		float direction;
		float drag;
		float dragCutoff;
		float maxSpeed;
		bool isPlayer;
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

#endif // !_COMPONENT_MOTION_H
