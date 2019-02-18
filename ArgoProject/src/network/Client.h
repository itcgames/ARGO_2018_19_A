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
		constexpr bool hasInit() const { return m_socket != NULL; }
		void closeSocket();
		bool checkSocket();
		bool processPacket(PacketType _packetType);

		bool sendAll(std::byte * data, int totalBytes);
		bool getAll(std::byte * data, int totalBytes);

		bool send(Lobby const & _lobby, app::net::PacketType const & _packet);
		bool get(Lobby & _lobby);

		bool send(const std::string& _string, const app::net::PacketType& _packetToProcessString);
		bool get(std::string& _string);

		bool send(const PacketType& _packetType);
		bool get(PacketType& _packetType);

		bool send(const int& _int);
		bool get(int& _int);
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
	private: // Private Static Variables
		constexpr static bool s_DEBUG_MODE = true;
	private: // Private Member Variables
		TCPsocket m_socket;
		SDLNet_SocketSet m_socketSet;

	};
}

#endif // !_NET_CLIENT_H
