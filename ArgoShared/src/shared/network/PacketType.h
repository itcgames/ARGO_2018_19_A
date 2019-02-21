#ifndef _NETWORK_PACKET_TYPE_H
#define _NETWORK_PACKET_TYPE_H

namespace app::net
{
	enum class PacketType
	{
		  UNKNOWN
		, CLIENT_NAME
		, LOBBY_CREATE
		, LOBBY_WAS_CREATED
		, LOBBY_GET_ALL
	};
}

#endif // !_NETWORK_PACKET_TYPE_H
