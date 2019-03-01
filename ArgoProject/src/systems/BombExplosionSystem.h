#ifndef _BOMB_EXPLOSION_SYSTEM_H
#define _BOMB_EXPLOSION_SYSTEM_H

#include "BaseSystem.h"

namespace app::sys
{
	class BombExplosionSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		BombExplosionSystem() = default;
		virtual ~BombExplosionSystem() = default;

		BombExplosionSystem(BombExplosionSystem const &) = default;
		BombExplosionSystem & operator=(BombExplosionSystem const &) = default;

		BombExplosionSystem(BombExplosionSystem &&) = default;
		BombExplosionSystem & operator=(BombExplosionSystem &&) = default;


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
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_BOMB_EXPLOSION_SYSTEM_H
