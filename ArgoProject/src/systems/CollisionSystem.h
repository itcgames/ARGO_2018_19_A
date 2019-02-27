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
		virtual void update(app::time::seconds const & dt) final override;
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables	
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
		void updateCollisionBoxes();
		void groundCollisions();
		void airCollisions();
		void dashCollisions();
		void enemyWallCollisions();
		void enemyEnemyCollisions();
		void playerHazardCollisions();
		void playerGoalCollisions();
		void playerEnemyCollisions();
		void checkPlatformCollisions();
		void checkAINodeCollisions();
		void AIHazardCollisions();
		void attackEnemyCollisions();
		void attackDestructibleCollisions();
		void checkDiscCollisions();
	private: // Private Static Variables
		constexpr static bool DEBUG_MODE = false;
	private: // Private Member Variables
	};
}

#endif // !_SYSTEM_COLLISION
