#ifndef _NET_CLIENT_H
#define _NET_CLIENT_H
#include"stdafx.h"

namespace app::net
{

	enum class Packet {
		CLIENT_NAME,
		LOBBY_CREATE
	};
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
		void closeSocket();
		bool initNetwork(std::string const & pIP, int iPort);
		bool checkSocket();
		bool processPacket(Packet _packetType);


		//Part of SendGetMethods cpp
		bool sendAll(std::byte * data, int totalBytes);
		bool getAll(std::byte * data, int totalBytes);

		bool send(const std::string& _string, const app::net::Packet& _packetToProcessString);
		bool get(std::string& _string);

		bool send(const Packet& _packetType);
		bool get(Packet& _packetType);

		bool send(const int& _int);
		bool get(int& _int);		
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
		TCPsocket m_socket;
		SDLNet_SocketSet m_socketSet;

	};
}

#endif // !_NET_CLIENT_H
