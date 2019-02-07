#ifndef _FACTORY_ENTITIES_H
#define _FACTORY_ENTITIES_H

#include "BaseFactory.h"
#include "EntityFactory.h"
#include "deleters/SdlDeleter.h"

namespace app::fact
{
	class EntitiesFactory : public BaseFactory<std::vector<app::Entity>>
	{
	public: // Constructors/Destructor/Assignments
		EntitiesFactory();
		virtual ~EntitiesFactory() = default;

		EntitiesFactory(EntitiesFactory const &) = default;
		EntitiesFactory & operator=(EntitiesFactory const &) = default;

		EntitiesFactory(EntitiesFactory &&) = default;
		EntitiesFactory & operator=(EntitiesFactory &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual std::vector<app::Entity> create() abstract;
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
		app::Registry & m_registry;
		app::del::UPtrRenderer const & m_renderer;
		app::fact::EntityFactory m_entityFactory;
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_FACTORY_ENTITIES_H
