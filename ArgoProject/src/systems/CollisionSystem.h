#ifndef _SYSTEM_COLLISION
#define _SYSTEM_COLLISION
#include "utilities/cute_c2.h"
#include "BaseSystem.h"

namespace app::sys
{
	class CollisionSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		CollisionSystem();
		~CollisionSystem() = default;	

		CollisionSystem(CollisionSystem const &) = default;
		CollisionSystem(CollisionSystem &&) = default;

		CollisionSystem & operator=(CollisionSystem const &) = default;
		CollisionSystem & operator=(CollisionSystem &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		std::string checkManifoldType(std::variant<cute::c2AABB, cute::c2Circle> &left, std::variant<cute::c2AABB, cute::c2Circle> &right);
		void updateAABB(cute::c2AABB c, app::math::Vector2<float> l, app::math::Vector2<float> d);
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

#endif // !_SYSTEM_COLLISION
