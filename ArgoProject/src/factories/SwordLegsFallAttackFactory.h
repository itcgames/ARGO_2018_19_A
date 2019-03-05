#ifndef _SWORD_LEGS_FALL_ATTACK_FACTORY_H
#define _SWORD_LEGS_FALL_ATTACK_FACTORY_H

#include "EntityFactory.h"

namespace app::fact
{
	class SwordLegsFallAttackFactory : public EntityFactory
	{
	public: // Constructors/Destructor/Assignments
		SwordLegsFallAttackFactory(app::Entity const _entity);
		~SwordLegsFallAttackFactory() = default;

		SwordLegsFallAttackFactory(SwordLegsFallAttackFactory const &) = default;
		SwordLegsFallAttackFactory & operator=(SwordLegsFallAttackFactory const &) = default;

		SwordLegsFallAttackFactory(SwordLegsFallAttackFactory &&) = default;
		SwordLegsFallAttackFactory & operator=(SwordLegsFallAttackFactory &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual app::Entity const create() override;
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

#endif // !_SWORD_LEGS_DASH_ATTACK_FACTORY_H
