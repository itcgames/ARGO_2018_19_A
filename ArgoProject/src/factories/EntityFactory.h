#ifndef _FACTORY_ENTITY_H
#define _FACTORY_ENTITY_H

#include "BaseFactory.h"

namespace app::fact
{
	class EntityFactory : public BaseFactory<app::Entity const>
	{
	public: // Constructors/Destructor/Assignments
		EntityFactory();
		virtual ~EntityFactory() = default;

		EntityFactory(EntityFactory const &) = default;
		EntityFactory & operator=(EntityFactory const &) = default;

		EntityFactory(EntityFactory &&) = default;
		EntityFactory & operator=(EntityFactory &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual app::Entity const create() override;
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
		app::Registry & m_registry;
		app::del::UPtrRenderer const & m_renderer;
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_FACTORY_ENTITY_H
