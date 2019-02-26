#ifndef _LOBBY_TAG_H
#define _LOBBY_TAG_H

#include "shared/network/Lobby.h"

namespace app::tag
{
	struct Lobby
	{
	public: // Constructors/Destructor/Assignments
		Lobby() = default;
		~Lobby() = default;

		Lobby(Lobby const &) = default;
		Lobby & operator=(Lobby const &) = default;

		Lobby(Lobby &&) = default;
		Lobby & operator=(Lobby &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		std::uint8_t id;
		std::string name;
		bool isHost = false;
		app::net::Lobby::Players players;
		std::size_t playerIndex;
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

#endif // !_LOBBY_TAG_H
