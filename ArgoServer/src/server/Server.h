#ifndef _SERVER_H
#define _SERVER_H

#include "shared/network/Lobby.h"
#include "shared/network/PacketType.h"

namespace app::net
{
	class Server
	{
	public: // Constructors/Destructor/Assignments
		Server(int _port);
		~Server();

		Server(Server const &) = default;
		Server & operator=(Server const &) = default;

		Server(Server &&) = default;
		Server & operator=(Server &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		bool listenForSockets();
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
		void clientHandlerThread(int ID, std::atomic<bool> & stopThread);
		void initServer(int _port);
		bool acceptSocket(int index);
		void closeSocket(int index);
		void sdlCleanup();

		bool getAll(int ID, std::byte * data, int totalBytes);
		bool sendAll(int ID, std::byte * data, int totalBytes);
		bool get(int ID, int& _int);
		bool get(int ID, std::string& _string);
		bool get(int ID, PacketType& _packetType);

		bool send(int ID, const int& _int);
		bool send(int ID, const PacketType& _packetType);
		bool send(int ID, const std::string& _string, const PacketType& _packetToProcessString);
		bool send(int ID, Lobby const & _lobby);
		bool processPacket(int ID, PacketType _packetType);

		// packet process functions

		bool processClientName(int id);
		bool processLobbyCreate(int id);
		bool processLobbyGetAll(int id);
		bool processDefault(int id);

		void outputIP(IPaddress const & ip);
		void output(int ID, std::string const & msg) const;
		void output(int ID, std::initializer_list<std::string> const & msgs) const;
	private: // Private Static Variables
		constexpr static int s_MAX_SOCKETS = 255;
		constexpr static bool s_DEBUG_MODE = true;
	private: // Private Member Variables
		// Contains thread instance
		std::map<std::int32_t, std::pair<std::optional<std::thread>, std::atomic<bool>>> m_clientThreads;
		//the servers socket
		TCPsocket m_serverSocket;
		//the socket set
		SDLNet_SocketSet m_socketSet;
		//array of sockets connected to server
		std::array<TCPsocket, s_MAX_SOCKETS> m_sockets;

		std::uint8_t m_totalConnections = 0u;

		std::vector<Lobby> m_lobbies;
	};
}
#endif // !_SERVER_H
