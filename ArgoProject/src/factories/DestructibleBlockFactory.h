#ifndef _FACTORY_DESTRUCTIBLE_BLOCK_H
#define _FACTORY_DESTRUCTIBLE_BLOCK_H

#include "EntitiesFactory.h"
#include "parameters/DestructibleParameters.h"
#include "deleters/SdlDeleter.h"
#include "graphics/Texture.h"

namespace app::fact
{
	class DestructibleBlockFactory : public EntitiesFactory
	{
	public: // Constructors/Destructor/Assignments
		DestructibleBlockFactory(app::par::DestructibleParameters param);
		virtual ~DestructibleBlockFactory() = default;

		DestructibleBlockFactory(DestructibleBlockFactory const &) = default;
		DestructibleBlockFactory & operator=(DestructibleBlockFactory const &) = default;

		DestructibleBlockFactory(DestructibleBlockFactory &&) = default;
		DestructibleBlockFactory & operator=(DestructibleBlockFactory &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual std::vector<app::Entity> create() override;
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
		app::par::DestructibleParameters parameters;
	};
}

#endif // !_FACTORY_DESTRUCTIBLE_BLOCK_H
