#ifndef _LOBBY_DISPLAY_FACTORY_H
#define _LOBBY_DISPLAY_FACTORY_H

#include "../EntitiesFactory.h"

namespace app::fact
{
	class LobbyDisplayFactory : public EntitiesFactory
	{
	public: // Constructors/Destructor/Assignments
		LobbyDisplayFactory(math::Vector2f const & position, std::string const & lobbyName);
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
	private: // Private Static Variables
	private: // Private Member Variables
		math::Vector2f const & m_position;
		std::string const & m_lobbyName;
	};
}

#endif // !_LOBBY_DISPLAY_FACTORY_H
