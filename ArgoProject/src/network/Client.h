#ifndef _NET_CLIENT_H
#define _NET_CLIENT_H

#include "shared/network/Lobby.h"
#include "shared/network/PacketType.h"

namespace app::net
{
	class Client
	{
	public: // Constructors/Destructor/Assignments
		Client() = default;
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

		bool sendAll(std::byte * data, int totalBytes);
		bool getAll(std::byte * data, int totalBytes);

		bool get(Lobby & _lobby);
		
		bool get(std::list<Lobby> & _lobbies);

		bool send(const std::string& _string);
		bool get(std::string& _string);

		bool send(const PacketType& _packetType);
		bool get(PacketType& _packetType);

		bool send(const int& _int);
		bool get(int& _int);

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
	private: // Private Member Functions
		void output(std::string const & msg) const;
		void output(std::initializer_list<std::string> const & msgs) const;

		bool processClientName();
		bool processLobbyWasCreated();
		bool processLobbyCreate();
		bool processDefault();
	private: // Private Static Variables
		constexpr static bool s_DEBUG_MODE = true;
	private: // Private Member Variables
		TCPsocket m_socket;
		SDLNet_SocketSet m_socketSet;
		std::vector<Lobby> m_lobbies;
	};
}

#endif // !_NET_CLIENT_H
