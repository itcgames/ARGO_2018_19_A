#ifndef _FACTORY_ENEMY_H
#define _FACTORY_ENEMY_H

#include "../EntityFactory.h"
#include "deleters/SdlDeleter.h"
#include "graphics/Texture.h"

namespace app::fact
{
	class EnemyFactory : public EntityFactory
	{
	public: // Constructors/Destructor/Assignments
		EnemyFactory();
		virtual ~EnemyFactory() = default;

		EnemyFactory(EnemyFactory const &) = default;
		EnemyFactory & operator=(EnemyFactory const &) = default;

		EnemyFactory(EnemyFactory &&) = default;
		EnemyFactory & operator=(EnemyFactory &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual app::Entity const create(math::Vector2f position, math::Vector2f size);
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

#endif // !_FACTORY_ENEMY_H
