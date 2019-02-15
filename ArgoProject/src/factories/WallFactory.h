#ifndef _FACTORY_WALL_H
#define _FACTORY_WALL_H


#include "EntityFactory.h"
#include "deleters/SdlDeleter.h"
#include "graphics/Texture.h"

namespace app::fact
{
	class WallFactory : public EntityFactory
	{
	public: // Constructors/Destructor/Assignments
		WallFactory(app::math::Vector2f const & pos, app::math::Vector2f const & size);
		virtual ~WallFactory() = default;

		WallFactory(WallFactory const &) = default;
		WallFactory & operator=(WallFactory const &) = default;

		WallFactory(WallFactory &&) = default;
		WallFactory & operator=(WallFactory &&) = default;

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

#endif // !_FACTORY_WALL_H
