#ifndef _AXE_ATTACK_FACTORY_H
#define _AXE_ATTACK_FACTORY_H

#include "../EntityFactory.h"

namespace app::fact
{
	class AxeAttackFactory : public EntityFactory
	{
	public: // Constructors/Destructor/Assignments
		AxeAttackFactory(app::Entity const _entity);
		~AxeAttackFactory() = default;

		AxeAttackFactory(AxeAttackFactory const &) = default;
		AxeAttackFactory & operator=(AxeAttackFactory const &) = default;

		AxeAttackFactory(AxeAttackFactory &&) = default;
		AxeAttackFactory & operator=(AxeAttackFactory &&) = default;

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

#endif // !_AXE_ATTACK_FACTORY_H
