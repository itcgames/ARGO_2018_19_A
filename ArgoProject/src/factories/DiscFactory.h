#ifndef _DISC_FACTORY_H
#define _DISC_FACTORY_H

#include "EntityFactory.h"

namespace app::fact
{
	class DiscFactory : public EntityFactory
	{
	public: // Constructors/Destructor/Assignments
		DiscFactory(app::Entity const _entity);
		~DiscFactory() = default;

		DiscFactory(DiscFactory const &) = default;
		DiscFactory & operator=(DiscFactory const &) = default;

		DiscFactory(DiscFactory &&) = default;
		DiscFactory & operator=(DiscFactory &&) = default;

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

#endif // !_DISC_FACTORY_H
