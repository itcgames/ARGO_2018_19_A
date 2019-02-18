#ifndef _NETWORK_PACKET_TYPE_H
#define _NETWORK_PACKET_TYPE_H

namespace app::net
{
	enum class PacketType
	{
		  UNKNOWN
		, CLIENT_NAME
		, LOBBY_CREATE
	};
}

#endif // !_NETWORK_PACKET_TYPE_H
