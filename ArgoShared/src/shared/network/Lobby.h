#ifndef _NETWORK_LOBBY_H
#define _NETWORK_LOBBY_H

namespace app::net
{
	class Lobby
	{
	public: // Usings/typedefs/enums
		using Player = std::optional<std::pair<std::int32_t, std::string>>;
		using Players = std::array<Player, 4>;
	public: // Constructors/Destructor/Assignments
		Lobby() = default;
		~Lobby() = default;

		Lobby(Lobby const &) = default;
		Lobby & operator=(Lobby const &) = default;

		Lobby(Lobby &&) noexcept = default;
		Lobby & operator=(Lobby &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		const std::string& getName() const;
		void setName(const std::string& name);

		Players & getPlayers() { return m_players; }
		Players const & getPlayers() const { return m_players; }
		std::optional<std::size_t> addPlayer(std::int32_t const & id, const std::string& name);

		std::uint8_t const & getId() const { return m_id; }
		void setId(std::uint8_t const & id) { m_id = id; }
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
		Players m_players;
		//name of the lobby
		std::string m_lobbyName;
		std::uint8_t m_id;
	};


}

#endif // !_NETWORK_LOBBY_H
