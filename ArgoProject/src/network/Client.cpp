#include "stdafx.h"
#include "Client.h"

app::net::Client::Client()
	: PacketParser()
	, m_socket()
	, m_socketSet()
	, m_lobbies()
{
}

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

void app::net::Client::setLobbies(std::list<Lobby>&& lobbies)
{
	m_lobbies.clear();
	m_lobbies.insert(m_lobbies.end()
		, std::make_move_iterator(lobbies.begin())
		, std::make_move_iterator(lobbies.end()));
}

bool app::net::Client::processClientName()
{
	auto clientName = std::string();
	if (!this->get(clientName)) { return false; }
	this->output({ "Received client name[", clientName, "]" });
	return true;
}

bool app::net::Client::processLobbyWasCreated()
{
	auto lobby = Lobby();
	if (!this->get(lobby)) { return false; }
	m_lobbies.insert(m_lobbies.end(), lobby);
	return true;
}

bool app::net::Client::processLobbyCreate()
{
	return true;
}

bool app::net::Client::processLobbyGetAll()
{
	auto lobbies = std::list<Lobby>();
	if (!this->get(lobbies)) { return false; }

	this->setLobbies(std::move(lobbies));
	return true;
}

bool app::net::Client::processDefault()
{
	this->output("No proccessing done for this packet type");
	return false;
}

bool app::net::Client::processPacket(PacketType _packetType)
{
	switch (_packetType)
	{
		case PacketType::CLIENT_NAME:
			return this->processClientName();
		case PacketType::LOBBY_WAS_CREATED:
			return this->processLobbyWasCreated();
		case PacketType::LOBBY_GET_ALL:
			return this->processLobbyGetAll();
		case PacketType::UNKNOWN:
			this->output("Unknown Packet type!");
		case PacketType::LOBBY_CREATE:
		default:
			return this->processDefault();
	}
	return false;
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
