#include "stdafx.h"
#include "ByteConverter.h"

/*
std::vector<std::byte> convertToBytes(std::int32_t const & number)
{
	constexpr auto ZERO_BYTE = static_cast<std::byte>(0u);
	auto bytes = std::vector<std::byte>();
	bytes.resize(sizeof(std::int32_t), ZERO_BYTE);
	auto const * pByte = reinterpret_cast<std::byte const *>(&number);
	for (std::size_t i = 0; i < bytes.size(); ++i) { bytes.at(i) = pByte[i]; }
	return std::move(bytes);
}

std::vector<std::byte> convertToBytes(std::string const & _string)
{
	constexpr auto ZERO_BYTE = static_cast<std::byte>(0u);
	auto bytes = std::vector<std::byte>();
	bytes.resize(_string.size());
	auto const * pByte = (std::byte const *)(_string.data());
	std::copy(pByte, pByte + _string.size(), bytes.begin());
	//for (std::size_t i = 0; i < bytes.size(); ++i) { bytes.at(i) = pByte[i]; }
	return std::move(bytes);
}

std::vector<std::byte> && convertToBytes(app::net::Lobby const & lobby)
{
	auto bytes = std::vector<std::byte>();
	bytes.reserve(sizeof(app::net::Lobby) + lobby.getPlayers().size());
	auto lobbyNameSizeBytes = convertToBytes(lobby.getName().size());
	bytes.insert(bytes.end()
		, std::make_move_iterator(lobbyNameSizeBytes.begin())
		, std::make_move_iterator(lobbyNameSizeBytes.end()));
	auto lobbyNameBytes = convertToBytes(lobby.getName());
	bytes.insert(bytes.end()
		, std::make_move_iterator(lobbyNameBytes.begin())
		, std::make_move_iterator(lobbyNameBytes.end()));
	auto lobbyNumberPlayersBytes = convertToBytes(lobby.getPlayers().size());
	bytes.insert(bytes.end()
		, std::make_move_iterator(lobbyNumberPlayersBytes.begin())
		, std::make_move_iterator(lobbyNumberPlayersBytes.end()));
	for (auto const &[id, playerName] : lobby.getPlayers())
	{
		auto idBytes = convertToBytes(id);
		bytes.insert(bytes.end()
			, std::make_move_iterator(idBytes.begin())
			, std::make_move_iterator(idBytes.end()));
		auto playerNameBytes = convertToBytes(playerName);
		bytes.insert(bytes.end()
			, std::make_move_iterator(playerNameBytes.begin())
			, std::make_move_iterator(playerNameBytes.end()));
	}
	return std::move(bytes);
}
/**/