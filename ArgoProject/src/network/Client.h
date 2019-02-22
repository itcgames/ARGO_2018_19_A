#ifndef _NET_CLIENT_H
#define _NET_CLIENT_H

#include "shared/network/Lobby.h"
#include "shared/network/PacketType.h"
#include "shared/utilities/ByteConverter.h"

namespace app::net
{
	class Client
	{
	private: // Usings/typedefs/enums
		using ByteConverter = app::util::ByteConverter;
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

		bool sendAll(std::vector<std::byte> const & data);
		bool getAll(std::vector<std::byte> & data);

		template<typename T>
		bool send(T const & t);
		template<typename T>
		bool get(T & t);

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
		std::optional<std::vector<std::byte>> getNextPacket(std::optional<std::size_t> packetSize = std::nullopt);

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

	template<typename T>
	bool Client::send(T const & t)
	{
		return sendAll(ByteConverter::convertTo(t));
	}

	template<>
	bool Client::get<Lobby>(Lobby & lobby)
	{
		auto packet = this->getNextPacket();
		if (!packet.has_value()) { return false; }

		lobby = ByteConverter::convertFrom<Lobby>(packet->cbegin(), packet->cend());
		return true;
	}

	template<>
	bool Client::get<std::list<Lobby>>(std::list<Lobby> & lobbies)
	{
		int numberOfLobbies = 0;
		if (!get(numberOfLobbies)) { return false; }

		auto tempLobbies = std::vector<Lobby>();
		lobbies.resize(numberOfLobbies);
		for (auto & lobby : tempLobbies)
		{
			if (!get(lobby)) { return false; }
		}

		lobbies.insert(lobbies.end()
			, std::make_move_iterator(tempLobbies.begin())
			, std::make_move_iterator(tempLobbies.end()));
		return true;
	}

	template<>
	bool Client::get<std::string>(std::string & str)
	{
		int bufferSize = 0;
		if (!get(bufferSize)) { return false; }

		auto packet = this->getNextPacket(bufferSize);
		if (!packet.has_value()) { return false; }

		str = ByteConverter::convertFrom<std::string>(packet->cbegin(), packet->cend());
		return true;
	}

	template<typename T>
	bool Client::get(T & t)
	{
		auto packet = this->getNextPacket(sizeof(T));
		if (!packet.has_value()) { return false; }

		t = ByteConverter::convertFrom<T>(packet->cbegin(), packet->cend());
		return true;
	}
}

#endif // !_NET_CLIENT_H
