#ifndef _SERVER_H
#define _SERVER_H

#include "stdafx.h"
#include <windows.h>

namespace app::net
{
	enum Packet {
		P_CLIENT_NAME
	};
	class Server
	{
	public: // Constructors/Destructor/Assignments
		Server(int _port);
		~Server() = default;

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
		static void clientHandlerThread(int ID);
	private: // Private Member Functions
		void initServer(int _port);
		bool acceptSocket(int index);
		void closeSocket(int index);
		void sdlCleanup();

		//part of sendgetmethods cpp
		bool recvAll(int ID, char* data, int totalBytes);
		bool sendAll(int ID, char* data, int totalBytes);
		bool sendInt(int ID, int _int);
		bool getInt(int ID, int& _int);
		bool sendPacketType(int ID, Packet _packetType);
		bool getPacketType(int ID, Packet& _packetType);
		bool send(int ID, std::string& _string, Packet& _packetToProcessString);
		bool getString(int ID, std::string& _string);
		bool processPacket(int ID, Packet _packetType);
	private: // Private Static Variables
		static const int MAX_SOCKETS = 16;
	private: // Private Member Variables
		//the servers socket
		TCPsocket server_socket;
		//the socket set
		SDLNet_SocketSet socket_set;
		//array of sockets connected to server
		TCPsocket sockets[MAX_SOCKETS];

		int totalConnections = 0;
	};
}

static app::net::Server * serverptr; //Serverptr is necessary so the static ClientHandler method can access the server instance/functions.
#endif // !_SERVER_H
