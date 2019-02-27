#ifndef _LOBBY_DISPLAY_FACTORY_PARAMETERS_H
#define _LOBBY_DISPLAY_FACTORY_PARAMETERS_H

#include "shared/network/Lobby.h"

namespace app::par
{
	struct LobbyDisplayFactoryParameters
	{
	public: // Constructors/Destructor/Assignments
		LobbyDisplayFactoryParameters() = default;
		~LobbyDisplayFactoryParameters() = default;

		LobbyDisplayFactoryParameters(LobbyDisplayFactoryParameters const &) = default;
		LobbyDisplayFactoryParameters & operator=(LobbyDisplayFactoryParameters const &) = default;

		LobbyDisplayFactoryParameters(LobbyDisplayFactoryParameters &&) = default;
		LobbyDisplayFactoryParameters & operator=(LobbyDisplayFactoryParameters &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		std::vector<app::Entity> entities;
		math::Vector2f position;
		std::vector<app::net::Lobby> lobbies;
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_LOBBY_DISPLAY_FACTORY_PARAMETERS_H
