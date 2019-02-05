#ifndef _FINITE_STATE_MACHINES_ENTITY_STATE_H
#define _FINITE_STATE_MACHINES_ENTITY_STATE_H

#include "../BaseState.h"

namespace app::fsm::sta
{
	class EntityState : public BaseState
	{
	public: // Constructors/Destructor/Assignments
		EntityState(app::Entity const entity);
		virtual ~EntityState() = default;

		EntityState(EntityState const &) = default;
		EntityState & operator=(EntityState const &) = default;

		EntityState(EntityState &&) = default;
		EntityState & operator=(EntityState &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
		app::Registry & m_registry;
		app::Entity const m_entity;
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_FINITE_STATE_MACHINES_ENTITY_STATE_H
