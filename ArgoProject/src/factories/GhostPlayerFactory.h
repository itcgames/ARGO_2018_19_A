#ifndef _FACTORY_GHOST_PLAYER_H
#define _FACTORY_GHOST_PLAYER_H

#include "EntityFactory.h"
#include "parameters/GhostPlayerFactoryParameters.h"

namespace app::fact
{
	class GhostPlayerFactory : public EntityFactory
	{
	public: // Constructors/Destructor/Assignments
		GhostPlayerFactory(app::par::GhostPlayerFactoryParameters const & params);
		virtual ~GhostPlayerFactory() = default;

		GhostPlayerFactory(GhostPlayerFactory const &) = default;
		GhostPlayerFactory & operator=(GhostPlayerFactory const &) = default;

		GhostPlayerFactory(GhostPlayerFactory &&) = default;
		GhostPlayerFactory & operator=(GhostPlayerFactory &&) = default;

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
		app::par::GhostPlayerFactoryParameters const & m_params;
	};
}

#endif // !_FACTORY_GHOST_PLAYER_H
