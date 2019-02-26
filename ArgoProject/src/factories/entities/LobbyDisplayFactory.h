#ifndef _LOBBY_DISPLAY_FACTORY_H
#define _LOBBY_DISPLAY_FACTORY_H

#include "../EntitiesFactory.h"
#include "parameters/LobbyDisplayFactoryParameters.h"
#include "scenes/SceneType.h"

namespace app::fact
{
	class LobbyDisplayFactory : public EntitiesFactory
	{
	public: // Constructors/Destructor/Assignments
		LobbyDisplayFactory(app::par::LobbyDisplayFactoryParameters const & params, app::sce::SceneType & sceneControl);
		virtual ~LobbyDisplayFactory() = default;

		LobbyDisplayFactory(LobbyDisplayFactory const &) = default;
		LobbyDisplayFactory & operator=(LobbyDisplayFactory const &) = default;

		LobbyDisplayFactory(LobbyDisplayFactory &&) = default;
		LobbyDisplayFactory & operator=(LobbyDisplayFactory &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual std::vector<app::Entity> create() final override;
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
		std::size_t getNumberOfPlayersIn(app::net::Lobby const & lobby) const;
	private: // Private Static Variables
	private: // Private Member Variables
		app::par::LobbyDisplayFactoryParameters const & m_params;
		app::sce::SceneType & m_sceneControl;
	};
}

#endif // !_LOBBY_DISPLAY_FACTORY_H
