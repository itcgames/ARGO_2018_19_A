#ifndef _FACTORY_HAZARD_H
#define _FACTORY_HAZARD_H

#include"EntityFactory.h"

namespace app::fact
{
	class HazardFactory : public EntityFactory
	{
	public: // Constructors/Destructor/Assignments
		HazardFactory(app::math::Vector2f const & pos, app::math::Vector2f const & size);
		virtual ~HazardFactory() = default;

		HazardFactory(HazardFactory const &) = default;
		HazardFactory& operator=(HazardFactory const &) = default;

		HazardFactory (HazardFactory &&) = default;
		HazardFactory & operator=(HazardFactory &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual app::Entity const create() override;
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
		app::math::Vector2f const & m_position;
		app::math::Vector2f const & m_size;
	};
}

#endif // !_FACTORY_HAZARD_H
