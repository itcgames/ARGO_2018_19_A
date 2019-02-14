#ifndef _FACTORY_PLATFORM_H
#define _FACTORY_PLATFORM_H

#include "./EntityFactory.h"

namespace app::fact
{
	class PlatformFactory : public EntityFactory
	{
	public: // Constructors/Destructor/Assignments
		PlatformFactory(app::math::Vector2f position, app::math::Vector2f size);
		virtual ~PlatformFactory() = default;

		PlatformFactory(PlatformFactory const &) = default;
		PlatformFactory & operator=(PlatformFactory const &) = default;

		PlatformFactory(PlatformFactory &&) = default;
		PlatformFactory & operator=(PlatformFactory &&) = default;


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
		app::math::Vector2f const m_position;
		app::math::Vector2f const m_size;
	};
}

#endif // !_FACTORY_PLATFORM_H
