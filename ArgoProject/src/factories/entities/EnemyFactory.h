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
		EnemyFactory(math::Vector2f const & position, math::Vector2f const & size);
		virtual ~EnemyFactory() = default;

		EnemyFactory(EnemyFactory const &) = default;
		EnemyFactory & operator=(EnemyFactory const &) = default;

		EnemyFactory(EnemyFactory &&) = default;
		EnemyFactory & operator=(EnemyFactory &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual app::Entity const create() final override;
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
		math::Vector2f const & m_position;
		math::Vector2f const & m_size;
	};
}

#endif // !_FACTORY_ENEMY_H
