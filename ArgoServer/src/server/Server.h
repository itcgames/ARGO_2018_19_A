#ifndef _SERVER_H
#define _SERVER_H

#include "stdafx.h"
#include "Lobby.h"
#include <windows.h>

namespace app::net
{
	enum class Packet {
		CLIENT_NAME,
		LOBBY_CREATE
	};
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
		bool get(int ID, Packet& _packetType);

		bool send(int ID, const int& _int);
		bool send(int ID, const Packet& _packetType);
		bool send(int ID, const std::string& _string, const Packet& _packetToProcessString);
		bool send(int ID, Lobby const & _lobby, Packet const & _packetType);
		bool processPacket(int ID, Packet _packetType);
		void outputIP(IPaddress const & ip);
	private: // Private Static Variables
		constexpr static int s_MAX_SOCKETS = 16;
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

		std::int32_t m_totalConnections = 0;

		std::vector<Lobby> m_lobbies;
	};
}
#endif // !_SERVER_H
