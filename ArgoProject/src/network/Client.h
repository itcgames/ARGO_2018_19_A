#ifndef _NET_CLIENT_H
#define _NET_CLIENT_H

#include "shared/network/Lobby.h"
#include "shared/network/PacketType.h"
#include "shared/network/PacketParser.h"

namespace app::net
{
	class Client : public app::net::PacketParser
	{
	private: // Usings/typedefs/enums
	public: // Constructors/Destructor/Assignments
		Client();
		~Client() = default;

		Client(Client const &) = default;
		Client & operator=(Client const &) = default;

		Client(Client &&) = default;
		Client & operator=(Client &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		bool initNetwork(std::string const & pIP, int iPort);
		bool deinitNetwork();
		constexpr bool hasInit() const { return m_socket != NULL; }
		void closeSocket();
		bool checkSocket();
		bool processPacket(PacketType _packetType);

		template<typename T> bool send(T const & t) const { return PacketParser::send(m_socket, t); }
		template<typename T> bool get(T & t) const { return PacketParser::get(m_socket, t); }

		constexpr std::vector<Lobby> const & getLobbies() const { return m_lobbies; }
		void setLobbies(std::list<Lobby> && lobbies);

	public: // Public Static Variables
		constexpr static auto s_SERVER_IP = "localhost";
		constexpr static auto s_SERVER_PORT = 27000;
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
		static void merge(std::vector<Lobby> & lobbies, Lobby const & lobby);
	private: // Private Member Functions
		bool processClientName();
		bool processLobbyWasCreated();
		bool processLobbyCreate();
		bool processLobbyGetAll();
		bool processLobbyJoined();
		bool processLobbyJoinedMy();
		bool processDefault();


		void output(std::string const & msg) const;
		void output(std::initializer_list<app::Console::Variant> const & msgs) const;
	private: // Private Static Variables
		constexpr static bool s_DEBUG_MODE = true;
	private: // Private Member Variables
		TCPsocket m_socket;
		SDLNet_SocketSet m_socketSet;
		std::vector<Lobby> m_lobbies;
		std::int32_t m_id;
	};
}

#endif // !_NET_CLIENT_H
