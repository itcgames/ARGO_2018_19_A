#ifndef _LOBBY_H
#define _LOBBY_H

namespace app::net
{
	class Lobby
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
		void setName(const std::string& name);
		const std::string& getName();
		void addPlayer(int ID, const std::string& name);
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
		//a map where the key is a players socket and value is their name
		std::map<int, std::string> m_players;
		//name of the lobby
		std::string m_lobbyName;
	};
}

#endif // !_LOBBY_H
