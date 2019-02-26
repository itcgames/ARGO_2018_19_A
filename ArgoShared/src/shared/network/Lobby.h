#ifndef _NETWORK_LOBBY_H
#define _NETWORK_LOBBY_H

namespace app::net
{
	class Lobby
	{
	private: // Usings/typedefs/enums
		using PlayerMap = std::map<std::int32_t, std::string>;
	public: // Constructors/Destructor/Assignments
		Lobby() = default;
		~Lobby() = default;

		Lobby(Lobby const &) = default;
		Lobby & operator=(Lobby const &) = default;

		Lobby(Lobby &&) noexcept = default;
		Lobby & operator=(Lobby &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		void setName(const std::string& name);
		const std::string& getName() const;
		void addPlayer(int id, const std::string& name);
		PlayerMap const & getPlayers() const { return m_players; }
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
		PlayerMap m_players;
		//name of the lobby
		std::string m_lobbyName;
	};


}

#endif // !_NETWORK_LOBBY_H
