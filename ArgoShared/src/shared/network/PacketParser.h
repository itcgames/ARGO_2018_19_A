#ifndef _NETWORK_PACKET_PARSER_H
#define _NETWORK_PACKET_PARSER_H

#include "shared/utilities/ByteConverter.h"

namespace app::net
{
	/// 
	/// @brief Inheritable class that gives access to packer parsing template functions
	/// @author Rafael Plugge
	/// 
	/// <summary>
	/// Due to the nature of template functions all member functions have their definitions stated
	/// within the header, this was resolve linker errors when using this class.
	/// </summary>
	class PacketParser
	{
	private: // Usings/typedefs/enums
		using ByteConverter = app::util::ByteConverter;
	public: // Constructors/Destructor/Assignments
		PacketParser() = default;
		~PacketParser() = default;

		PacketParser(PacketParser const &) = default;
		PacketParser & operator=(PacketParser const &) = default;

		PacketParser(PacketParser &&) = default;
		PacketParser & operator=(PacketParser &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions

		template<typename T> static bool send(TCPsocket socket, T const & t)
		{
			return sendAll(socket, ByteConverter::convertTo(t));
		}

		#pragma region send template specializations

		#pragma endregion


		template<typename T> static bool get(TCPsocket socket, T & t)
		{
			auto packet = getNextPacket(socket, sizeof(T));
			if (!packet.has_value()) { return false; }

			t = ByteConverter::convertFrom<T>(packet->cbegin(), packet->cend());
			return true;
		}

		#pragma region get template specializations

		template<> static bool get<std::string>(TCPsocket socket, std::string & str)
		{
			int bufferSize = 0;
			if (!get(socket, bufferSize)) { return false; }

			auto packet = getNextPacket(socket, bufferSize);
			if (!packet.has_value()) { return false; }

			str = ByteConverter::convertFrom<std::string>(packet->cbegin(), packet->cend());
			return true;
		}

		template<> static bool get<app::net::Lobby>(TCPsocket socket, Lobby & lobby)
		{
			auto packet = getNextPacket(socket);
			if (!packet.has_value()) { return false; }

			lobby = ByteConverter::convertFrom<Lobby>(packet->cbegin(), packet->cend());
			return true;
		}

		template<> static bool get<std::list<app::net::Lobby>>(TCPsocket socket, std::list<Lobby> & lobbies)
		{
			int numberOfLobbies = 0;
			if (!get(socket, numberOfLobbies)) { return false; }

			auto tempLobbies = std::vector<Lobby>();
			tempLobbies.resize(numberOfLobbies);
			for (auto & lobby : tempLobbies)
			{
				if (!get(socket, lobby)) { return false; }
			}

			lobbies.insert(lobbies.end()
				, std::make_move_iterator(tempLobbies.begin())
				, std::make_move_iterator(tempLobbies.end()));
			return true;
		}

		#pragma endregion

	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
		static bool sendAll(TCPsocket socket, std::vector<std::byte> const & data)
		{
			int amountSent = 0;
			for (auto itt = data.cbegin(), end = data.cend(); itt != end; itt += amountSent)
			{
				amountSent = SDLNet_TCP_Send(socket, &(*itt), end - itt);
				if (amountSent <= 0) { return false; }
			}
			return true;
		}

		static bool getAll(TCPsocket socket, std::vector<std::byte> & data)
		{
			int amountReceived = 0;
			for (auto itt = data.begin(), end = data.end(); itt != end; itt += amountReceived)
			{
				amountReceived = SDLNet_TCP_Recv(socket, &(*itt), end - itt);
				if (amountReceived <= 0) { return false; }
			}

			return true;
		}

		static std::optional<std::vector<std::byte>> getNextPacket(TCPsocket socket, std::optional<std::size_t> packetSize = std::nullopt)
		{
			if (!packetSize.has_value())
			{
				packetSize = 0u;
				if (!get(socket, packetSize.value())) { return std::nullopt; }
			}

			auto bytes = std::vector<std::byte>();
			bytes.resize(packetSize.value());
			if (!getAll(socket, bytes)) { return std::nullopt; }
			return bytes;
		}

	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_NETWORK_PACKET_PARSER_H
