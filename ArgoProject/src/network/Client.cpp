#include "stdafx.h"
#include "Client.h"

/// <summary>
/// This function will close the socket.
/// </summary>
void app::net::Client::closeSocket()
{
	if (SDLNet_TCP_DelSocket(m_socketSet, m_socket) == -1)
	{
		app::Console::writeLine({ "ERROR: SDLNet_TCP_DelSocket [", SDLNet_GetError(), "]" });
	}
	SDLNet_FreeSocketSet(m_socketSet);
	SDLNet_TCP_Close(m_socket);
}

/// <summary>
/// Initialize the network, attempt to connect to server
/// </summary>
/// <param name="pIP">Ip to connect to</param>
/// <param name="iPort">port to connect through</param>
/// <returns>true if success, false if connection cant be established</returns>
bool app::net::Client::initNetwork(std::string const & pIP, int iPort)
{
	m_socketSet = SDLNet_AllocSocketSet(1);

	auto ipAddress = IPaddress();

	if (SDLNet_ResolveHost(&ipAddress, pIP.c_str(), iPort) != NULL)
	{
		app::Console::writeLine({ "ERROR: SDLNet_ResolveHost: [", SDLNet_GetError(), "]" });
	}
	// Get our IP address in proper dot-quad format by breaking up the 32-bit unsigned host address and splitting it into an array of four 8-bit unsigned numbers...
	Uint8 * dotQuad = (Uint8*)&ipAddress.host;
	//... and then outputting them cast to integers. Then read the last 16 bits of the serverIP object to get the port number
	std::cout << "Successfully resolved server host to IP: " << (unsigned short)dotQuad[0] << "." << (unsigned short)dotQuad[1] << "." << (unsigned short)dotQuad[2] << "." << (unsigned short)dotQuad[3];
	std::cout << " port " << SDLNet_Read16(&ipAddress.port) << std::endl << std::endl;
	
	//open the servers socket
	m_socket = SDLNet_TCP_Open(&ipAddress);
	if (m_socket == NULL)
	{
		app::Console::writeLine({ "ERROR: SDLNer_TCP_Open: [", SDLNet_GetError(), "]" });
		return false;
	}

	if (SDLNet_TCP_AddSocket(m_socketSet, m_socket) == -1)
	{
		app::Console::writeLine({ "ERROR: SDLNet_TCP_AddSocket: [", SDLNet_GetError(), "]" });
		return false;
	}
	m_lobbies.clear();
	m_lobbies.reserve(10);

	return true;
}

bool app::net::Client::deinitNetwork()
{
	try
	{
		SDLNet_TCP_DelSocket(m_socketSet, m_socket);
	}
	catch (std::exception const &)
	{
		app::Console::writeLine({ "ERROR: SDLNet_TCP_DelSocket: [", SDLNet_GetError(), "]" });
	}
	try
	{
		SDLNet_TCP_Close(m_socket);
	}
	catch (std::exception const &)
	{
		app::Console::writeLine({ "ERROR: SDLNet_TCP_Close: [", SDLNet_GetError(), "]" });
	}
	m_socket = NULL;
	try
	{
		SDLNet_FreeSocketSet(m_socketSet);
	}
	catch (std::exception const &)
	{
		app::Console::writeLine({ "ERROR: SDLNet_FreeSocketSet: [", SDLNet_GetError(), "]" });
	}
	m_socketSet = NULL;
	m_lobbies.clear();
	m_lobbies.reserve(10);

	return true;
}

/// <summary>
/// Check if the socket is ready to send/receive data
/// </summary>
/// <returns></returns>
bool app::net::Client::checkSocket()
{
	if (SDLNet_CheckSockets(m_socketSet, 0) == -1)
	{
		this->output({ "ERROR: SDLNet_CheckSockets [", SDLNet_GetError(), "]" });
		return false;
	}
	return SDLNet_SocketReady(m_socket);
}

bool app::net::Client::sendAll(std::vector<std::byte> const & data)
{
	int amountSent = 0;
	for (auto itt = data.cbegin(), end = data.cend(); itt != end; itt += amountSent)
	{
		amountSent = SDLNet_TCP_Send(m_socket, &(*itt), end - itt);
		if (amountSent < 0) { return false; }
		itt += amountSent;
	}
	return true;
}

bool app::net::Client::getAll(std::vector<std::byte>& data)
{
	int amountReceived = 0;
	for (auto itt = data.begin(), end = data.end(); itt != end; itt += amountReceived)
	{
		amountReceived = SDLNet_TCP_Recv(m_socket, &(*itt), end - itt);
		if (amountReceived < 0) { return false; }
	}

	return true;
}

void app::net::Client::setLobbies(std::list<Lobby>&& lobbies)
{
	m_lobbies.insert(m_lobbies.end()
		, std::make_move_iterator(lobbies.begin())
		, std::make_move_iterator(lobbies.end()));
}

std::optional<std::vector<std::byte>> app::net::Client::getNextPacket(std::optional<std::size_t> packetSize)
{
	if (!packetSize.has_value())
	{
		packetSize = 0u;
		if (!get(packetSize.value())) { return std::nullopt; }
	}

	auto bytes = std::vector<std::byte>();
	bytes.resize(packetSize.value());
	if (!getAll(bytes)) { return std::nullopt; }
	return bytes;
}

void app::net::Client::output(std::string const & msg) const
{
	if constexpr (s_DEBUG_MODE)
	{
		app::Console::write("CLIENT: ");
		app::Console::writeLine(msg);
	}
}

void app::net::Client::output(std::initializer_list<std::string> const & msgs) const
{
	if constexpr (s_DEBUG_MODE)
	{
		app::Console::write("CLIENT: ");
		app::Console::writeLine(msgs);
	}
}

bool app::net::Client::processClientName()
{
	auto clientName = std::string();
	if (!get(clientName))
	{
		return false;
	}
	this->output({ "Received client name[", clientName, "]" });
	return true;
}

bool app::net::Client::processLobbyWasCreated()
{
	throw std::exception("Not implemented");
	auto lobbies = std::list<Lobby>();
	return send(PacketType::LOBBY_GET_ALL) && get(lobbies);
}

bool app::net::Client::processLobbyCreate()
{
	return true;
}

bool app::net::Client::processDefault()
{
	this->output("No proccessing done for this packet type");
	return false;
}

/// <summary>
/// Process a packet based on the type of packet received.
/// </summary>
/// <param name="_packetType">type of received packet</param>
/// <returns>true if processes successfuly, false if fails processing</returns>
bool app::net::Client::processPacket(PacketType _packetType)
{
	switch (_packetType)
	{
		case PacketType::CLIENT_NAME:
			return this->processClientName();
		case PacketType::LOBBY_WAS_CREATED:
			return this->processLobbyWasCreated();
		case PacketType::UNKNOWN:
			this->output("Unknown Packet type!");
		case PacketType::LOBBY_CREATE:
		default:
			return this->processDefault();
	}
	return false;
}










