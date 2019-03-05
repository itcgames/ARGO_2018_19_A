#ifndef _SERVER_H
#define _SERVER_H

#include "shared/network/PacketType.h"
#include "shared/network/PacketParser.h"

namespace app::net
{
	class Server : public PacketParser
	{
	private: // Usings/typedefs/enums
		using ByteConverter = app::util::ByteConverter;
	public: // Constructors/Destructor/Assignments
		explicit Server(int port);
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
		void clientHandlerThread(int id, std::atomic<bool> & stopThread);
		void initServer(int port);
		bool acceptSocket(int index);
		void closeSocket(int index);
		void sdlCleanup();
		std::uint8_t getFreeSocket(std::uint8_t startIndex) const;

		template<typename T> bool get(int id, T & t) const { return PacketParser::get(m_sockets.at(id), t); }
		template<typename T> bool send(int id, T const & t) const { return PacketParser::send(m_sockets.at(id), t); }

		bool processPacket(int id, PacketType packetType);

		// packet process functions

		bool processClientName(int id);
		bool processLobbyReady(int id);
		bool processLobbyCreate(int id);
		bool processLobbyGetAll(int id);
		bool processLobbyJoined(int id);
		bool processLevelNewPlayerInfo(int id);
		bool processLobbyReady(int id);
		bool processDefault(int id);

		void outputIP(IPaddress const & ip);
		void output(int id, std::string const & msg) const;
		void output(int id, std::initializer_list<app::Console::Variant> const & msgs) const;
	private: // Private Static Variables
		constexpr static auto s_MAX_SOCKETS = std::numeric_limits<std::uint8_t>::max();
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
		std::uint8_t m_freeSocket = 0u;

		std::vector<Lobby> m_lobbies;
		std::uint8_t m_idGenerator = 0u;
	};
}
#endif // !_SERVER_H
