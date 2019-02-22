#ifndef _UTILITIES_BYTE_CONVERTER_H
#define _UTILITIES_BYTE_CONVERTER_H

#include "shared/network/Lobby.h"

namespace app::util
{
	class ByteConverter
	{
	private: // Usings/typedefs/enums
		using ByteIterator = std::vector<std::byte>::const_iterator;
	public: // Constructors/Destructor/Assignments
		ByteConverter() = delete;
		~ByteConverter() = delete;

		ByteConverter(ByteConverter const &) = delete;
		ByteConverter & operator=(ByteConverter const &) = delete;

		ByteConverter(ByteConverter &&) = delete;
		ByteConverter & operator=(ByteConverter &&) = delete;

	public: // Public Static Functions
		template<typename T>
		static std::vector<std::byte> convertTo(T const & t);
		template<typename T>
		static T convertFrom(ByteConverter::ByteIterator begin, ByteConverter::ByteIterator end);
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
		constexpr static auto s_ZERO_BYTE = static_cast<std::byte>(0);
	private: // Private Member Variables
	};


	template <>
	std::vector<std::byte> app::util::ByteConverter::convertTo<std::string>(std::string const & str)
	{
		auto bytes = std::vector<std::byte>();

		bytes.resize(sizeof(std::size_t) + str.size(), s_ZERO_BYTE);
		auto strSizeBytes = ByteConverter::convertTo(str.size());
		auto itt = bytes.insert(bytes.begin()
			, std::make_move_iterator(strSizeBytes.begin())
			, std::make_move_iterator(strSizeBytes.end()));

		auto const * pByte = reinterpret_cast<std::byte const *>(str.data());
		std::copy(pByte, pByte + str.size(), itt);

		return std::move(bytes);
	}

	template <>
	std::vector<std::byte> app::util::ByteConverter::convertTo<app::net::Lobby>(app::net::Lobby const & lobby)
	{
		auto bytes = std::vector<std::byte>();

		auto lobbyNameBytes = ByteConverter::convertTo(lobby.getName());
		bytes.insert(bytes.end()
			, std::make_move_iterator(lobbyNameBytes.begin())
			, std::make_move_iterator(lobbyNameBytes.end()));
		auto lobbyNumberPlayersBytes = ByteConverter::convertTo(lobby.getPlayers().size());
		bytes.insert(bytes.end()
			, std::make_move_iterator(lobbyNumberPlayersBytes.begin())
			, std::make_move_iterator(lobbyNumberPlayersBytes.end()));
		for (auto const &[id, playerName] : lobby.getPlayers())
		{
			auto idBytes = ByteConverter::convertTo(id);
			bytes.insert(bytes.end()
				, std::make_move_iterator(idBytes.begin())
				, std::make_move_iterator(idBytes.end()));
			auto playerNameBytes = ByteConverter::convertTo(playerName);
			bytes.insert(bytes.end()
				, std::make_move_iterator(playerNameBytes.begin())
				, std::make_move_iterator(playerNameBytes.end()));
		}

		return std::move(bytes);
	}

	template<typename T>
	std::vector<std::byte> ByteConverter::convertTo(T const & t)
	{
		auto bytes = std::vector<std::byte>();

		bytes.resize(sizeof(T), s_ZERO_BYTE);
		auto const * pByte = reinterpret_cast<std::byte const *>(&t);
		std::copy(pByte, pByte + sizeof(T), bytes.begin());

		return std::move(bytes);
	}

	template <>
	std::string app::util::ByteConverter::convertFrom<std::string>(ByteConverter::ByteIterator begin, ByteConverter::ByteIterator end)
	{
		auto str = std::string();

		str.resize(end - begin);
		auto * pStr = reinterpret_cast<std::byte *>(str.data());
		std::copy(begin, end, pStr);

		return std::move(str);
	}

	template <>
	app::net::Lobby ByteConverter::convertFrom<app::net::Lobby>(ByteConverter::ByteIterator begin, ByteConverter::ByteIterator end)
	{
		auto lobby = app::net::Lobby();

		end = begin + sizeof(std::size_t);		// move end iterator to the end of the first segment of the byte sequence
		// First we need to get the size of the lobby name
		auto lobbyNameSize = ByteConverter::convertFrom<std::size_t>(begin, end);

		// than we move the iterators forward by the amount of bytes the size takes
		begin = end;							// set the begin iterator to where the name starts in the byte vector
		end += lobbyNameSize;					// move the end iterator by the size of the name we are expecting to read.
		// convert the lobby name from the bytes
		auto lobbyName = ByteConverter::convertFrom<std::string>(begin, end);
		lobby.setName(lobbyName);

		begin = end;							// set the begin iterator to where the name ends in the byte vector
		end += sizeof(std::int32_t);			// move the end iterator by the expected size of a 32-bit signed integer
		// Get the number of players in the lobby (expect a int32)
		auto const NUMBER_OF_PLAYERS_IN_LOBBY = ByteConverter::convertFrom<std::int32_t>(begin, end);

		for (std::int32_t i = 0; i < NUMBER_OF_PLAYERS_IN_LOBBY; ++i)
		{
			begin = end;						// set the begin iterator to where the previous data ended
			end += sizeof(std::int32_t);		// move the end iterator by the expected size of a 32-bit signed integer
			auto const PLAYER_ID = ByteConverter::convertFrom<std::int32_t>(begin, end);

			begin = end;						// set the begin iterator to where the previous data ended
			end += sizeof(std::size_t);			// move the end iterator by the expected size of size_t
			auto const PLAYER_NAME_SIZE = ByteConverter::convertFrom<std::size_t>(begin, end);

			begin = end;						// set the begin iterator to where the previous data ended
			end += PLAYER_NAME_SIZE;			// move the end iterator by the size of the player name
			auto playerName = ByteConverter::convertFrom<std::string>(begin, end);

			lobby.addPlayer(PLAYER_ID, playerName);
		}

		return std::move(lobby);
	}

	template <typename T>
	T ByteConverter::convertFrom(ByteConverter::ByteIterator begin, ByteConverter::ByteIterator end)
	{
		auto t = T();

		auto * pT = reinterpret_cast<std::byte *>(&t);
		std::copy(begin, end, pT);

		return std::move(t);
	}
}

#endif // !_UTILITIES_BYTE_CONVERTER_H
