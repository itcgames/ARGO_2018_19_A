#ifndef _UTILITIES_BYTE_CONVERTER_H
#define _UTILITIES_BYTE_CONVERTER_H

#include "shared/network/Lobby.h"

namespace app::util
{
	class ByteConverter
	{
	private: // Usings/typedefs/enums
		using ByteConstIterator = std::vector<std::byte>::const_iterator;
	public: // Constructors/Destructor/Assignments
		ByteConverter() = delete;
		~ByteConverter() = delete;

		ByteConverter(ByteConverter const &) = delete;
		ByteConverter & operator=(ByteConverter const &) = delete;

		ByteConverter(ByteConverter &&) = delete;
		ByteConverter & operator=(ByteConverter &&) = delete;

	public: // Public Static Functions
		template<typename T>
		static std::vector<std::byte> convertTo(T const & t)
		{
			auto bytes = std::vector<std::byte>();

			bytes.resize(sizeof(T), s_ZERO_BYTE);
			auto const * pByte = reinterpret_cast<std::byte const *>(&t);
			std::copy(pByte, pByte + sizeof(T), bytes.begin());

			return std::move(bytes);
		}

		#pragma region convertTo template specializations

		template <> static std::vector<std::byte> convertTo<app::net::Lobby::Player>(app::net::Lobby::Player const & player)
		{
			auto bytes = std::vector<std::byte>();

			bytes.reserve(sizeof(bool));
			auto hasValueBytes = ByteConverter::convertTo(player.has_value());
			bytes.insert(bytes.end()
				, std::make_move_iterator(hasValueBytes.begin())
				, std::make_move_iterator(hasValueBytes.end()));
			if (player.has_value())
			{
				auto const &[id, name] = player.value();
				auto idBytes = convertTo(id);
				bytes.insert(bytes.end()
					, std::make_move_iterator(idBytes.begin())
					, std::make_move_iterator(idBytes.end()));
				auto nameBytes = convertTo(name);
				bytes.insert(bytes.end()
					, std::make_move_iterator(nameBytes.begin())
					, std::make_move_iterator(nameBytes.end()));
			}
			return std::move(bytes);
		}

		template <> static std::vector<std::byte> convertTo<std::string>(std::string const & str)
		{
			auto bytes = std::vector<std::byte>();

			bytes.reserve(sizeof(std::size_t) + str.size());
			auto strSizeBytes = ByteConverter::convertTo(str.size());
			bytes.insert(bytes.begin()
				, std::make_move_iterator(strSizeBytes.begin())
				, std::make_move_iterator(strSizeBytes.end()));

			auto const * pByte = reinterpret_cast<std::byte const *>(str.data());
			bytes.insert(bytes.end(), pByte, pByte + str.size());

			return std::move(bytes);
		}

		template <> static std::vector<std::byte> convertTo<app::net::Lobby>(app::net::Lobby const & lobby)
		{
			auto bytes = std::vector<std::byte>();

			auto lobbyNameBytes = ByteConverter::convertTo(lobby.getName());
			bytes.insert(bytes.end()
				, std::make_move_iterator(lobbyNameBytes.begin())
				, std::make_move_iterator(lobbyNameBytes.end()));
			auto lobbyIdBytes = ByteConverter::convertTo(lobby.getId());
			bytes.insert(bytes.end()
				, std::make_move_iterator(lobbyIdBytes.begin())
				, std::make_move_iterator(lobbyIdBytes.end()));
			auto lobbyNumberPlayersBytes = ByteConverter::convertTo(lobby.getPlayers().size());
			bytes.insert(bytes.end()
				, std::make_move_iterator(lobbyNumberPlayersBytes.begin())
				, std::make_move_iterator(lobbyNumberPlayersBytes.end()));
			for (auto const & playerName : lobby.getPlayers())
			{
				auto playerNameBytes = ByteConverter::convertTo(playerName);
				bytes.insert(bytes.end()
					, std::make_move_iterator(playerNameBytes.begin())
					, std::make_move_iterator(playerNameBytes.end()));
			}

			auto lobbySizeBytes = ByteConverter::convertTo(bytes.size());
			bytes.insert(bytes.begin()
				, std::make_move_iterator(lobbySizeBytes.begin())
				, std::make_move_iterator(lobbySizeBytes.end()));

			return std::move(bytes);
		}


		#pragma endregion

		template<typename T>
		static T convertFrom(ByteConverter::ByteConstIterator begin, ByteConverter::ByteConstIterator end)
		{
			auto t = T();

			auto * pT = reinterpret_cast<std::byte *>(&t);
			std::copy(begin, end, pT);

			return std::move(t);
		}

		#pragma region convertFrom template specializations

		template <> static std::string convertFrom<std::string>(ByteConverter::ByteConstIterator begin, ByteConverter::ByteConstIterator end)
		{
			auto str = std::string();

			str.resize(end - begin);
			auto * pStr = reinterpret_cast<std::byte *>(str.data());
			std::copy(begin, end, pStr);

			return std::move(str);
		}

		template <> static std::optional<std::string> convertFrom<std::optional<std::string>>(ByteConverter::ByteConstIterator begin, ByteConverter::ByteConstIterator end)
		{
			auto optionalText = std::optional<std::string>();

			auto hasValue = ByteConverter::convertFrom<bool>(begin, begin + sizeof(bool));

			if (hasValue)
			{
				begin += sizeof(bool);
				auto text = ByteConverter::convertFrom<std::string>(begin, end);
				optionalText.emplace(std::move(text));
			}

			return optionalText;
		}

		template <> static app::net::Lobby convertFrom<app::net::Lobby>(ByteConverter::ByteConstIterator begin, ByteConverter::ByteConstIterator end)
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

			begin = end;
			end += sizeof(std::uint8_t);
			// convert lobby id from the bytes
			auto lobbyId = ByteConverter::convertFrom<std::uint8_t>(begin, end);
			lobby.setId(lobbyId);

			begin = end;							// set the begin iterator to where the name ends in the byte vector
			end += sizeof(std::size_t);				// move the end iterator by the expected size of size_t
			// Get the number of players in the lobby (expect a int32)
			auto const NUMBER_OF_PLAYERS_IN_LOBBY = static_cast<std::int32_t>(ByteConverter::convertFrom<std::size_t>(begin, end));

			for (std::int32_t i = 0; i < NUMBER_OF_PLAYERS_IN_LOBBY; ++i)
			{
				begin = end;
				end += sizeof(bool);
				auto const HAS_PLAYER = ByteConverter::convertFrom<bool>(begin, end);

				if (HAS_PLAYER)
				{
					begin = end;
					end += sizeof(std::int32_t);
					auto const PLAYER_ID = ByteConverter::convertFrom<std::int32_t>(begin, end);

					begin = end;						// set the begin iterator to where the previous data ended
					end += sizeof(std::size_t);			// move the end iterator by the expected size of size_t
					auto const PLAYER_NAME_SIZE = ByteConverter::convertFrom<std::size_t>(begin, end);

					begin = end;						// set the begin iterator to where the previous data ended
					end += PLAYER_NAME_SIZE;			// move the end iterator by the size of the player name
					auto playerName = ByteConverter::convertFrom<std::string>(begin, end);

					lobby.addPlayer(PLAYER_ID, playerName);
				}

			}

			return std::move(lobby);
		}

		#pragma endregion

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
}

#endif // !_UTILITIES_BYTE_CONVERTER_H
