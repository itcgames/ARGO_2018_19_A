#ifndef _BOMB_ATTACK_FACTORY_H
#define _BOMB_ATTACK_FACTORY_H

#include "EntityFactory.h"

namespace app::fact
{
	class BombAttackFactory : public EntityFactory
	{
	public: // Constructors/Destructor/Assignments
		BombAttackFactory(app::Entity const m_entity);
		virtual ~BombAttackFactory() = default;

		BombAttackFactory(BombAttackFactory const &) = default;
		BombAttackFactory & operator=(BombAttackFactory const &) = default;

		BombAttackFactory(BombAttackFactory &&) = default;
		BombAttackFactory & operator=(BombAttackFactory &&) = default;


	public: // Public Static Functions
	public: // Public Member Functions
		virtual app::Entity const create() final override;
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
		constexpr static bool DEBUG_MODE = true;
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
		app::Entity const m_entity;

	};
}

#endif // !_BOMB_ATTACK_FACTORY_H
