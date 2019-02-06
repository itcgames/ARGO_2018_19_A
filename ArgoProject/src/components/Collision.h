#ifndef _COLLISION_H
#define _COLLISION_H

#include "math/Vector2.h"

namespace app::comp
{
	class Collision
	{
	public: // Constructors/Destructor/Assignments
		Collision() = default;
		~Collision() = default;

		Collision(Collision const &) = default;
		Collision & operator=(Collision const &) = default;

		Collision(Collision &&) = default;
		Collision & operator=(Collision &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		cute::c2AABB aabb;
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

#endif // !_Collision_H
