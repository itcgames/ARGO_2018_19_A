#ifndef _FACTORY_HAZARD_H
#define _FACTORY_HAZARD_H

#include"EntityFactory.h"
#include "deleters/SdlDeleter.h"
#include "graphics/Texture.h"

namespace app::fact
{
	struct HazardFactory : public EntityFactory
	{
	public: // Constructors/Destructor/Assignments
		HazardFactory(app::math::Vector2f pos, app::math::Vector2f size);
		~HazardFactory() = default;

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
		std::shared_ptr<app::gra::Texture> m_texture;
		app::math::Vector2f const m_position;
		app::math::Vector2f const m_size;
	};
}

#endif // !_FACTORY_HAZARD_H
