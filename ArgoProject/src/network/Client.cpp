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

/// <summary>
/// Send all type of data.
/// </summary>
/// <param name="data">data to send</param>
/// <param name="totalBytes">amount of bytes to send</param>
/// <returns>true if succeeds, false if the sending fails</returns>
bool app::net::Client::sendAll(std::byte * data, int totalBytes)
{

	//Holds the total bytes sent
	int bytesSent = 0;
	//while we still have more bytes to send
	while (bytesSent < totalBytes)
	{
		//try to send remaining bytes
		int RetnCheck = SDLNet_TCP_Send(m_socket, data + bytesSent, totalBytes - bytesSent);
		//if theres an error return false.
		if (RetnCheck < bytesSent)
		{
			return false;
		}
		//add to total bytes sent
		bytesSent += RetnCheck;
	}
	//success!
	return true;
}

/// <summary>
/// Send a string to the server. 
/// </summary>
/// <param name="_string">string to send</param>
/// <param name="_packetToProcessString">the packet type</param>
/// <returns>true if success, false if sending fails</returns>
bool app::net::Client::send(const std::string & _string, const app::net::PacketType& _packetType)
{
	app::net::PacketType type = _packetType;
	if (!send(type))
	{
		return false;
	}
	int bufferLen = _string.size();
	if (!send(bufferLen))
	{
		return false;
	}
	if (!sendAll((std::byte *)_string.c_str(), bufferLen))
	{
		return false;
	}
	return true;
}

/// <summary>
/// Expect a string from server.
/// </summary>
/// <param name="_string">string that will get assigned the value of received string</param>
/// <returns>true if success, false if receiving of data fails</returns>
bool app::net::Client::get(std::string & _string)
{
	int bufferLength;
	if (!get(bufferLength))
	{
		return false;
	}
	std::byte * buffer = new std::byte[bufferLength + 1];
	buffer[bufferLength] = static_cast<std::byte>('\0');
	if (!getAll(buffer, bufferLength))
	{
		delete[] buffer;
		return false;
	}
	_string = reinterpret_cast<char *>(buffer);
	delete[] buffer;
	return true;
}


/// <summary>
/// Send the packet type to server
/// </summary>
/// <param name="_packetType">packet type to send</param>
/// <returns>true if succeeds, false if sending fails</returns>
bool app::net::Client::send(const PacketType& _packetType)
{
	if (!sendAll((std::byte *)&_packetType, sizeof(PacketType)))
	{
		return false;
	}
	return true;
}

/// <summary>
/// Send an integer to the server
/// </summary>
/// <param name="_int">integer value to send</param>
/// <returns>true if succeeds, false if sending fails</returns>
bool app::net::Client::send(const int& _int)
{
	if (!sendAll((std::byte *)&_int, sizeof(int)))
	{
		return false;
	}
	return true;
}

/// <summary>
/// receive all types of data
/// </summary>
/// <param name="data">data that got received</param>
/// <param name="totalBytes">size of data</param>
/// <returns>true if success, false if fail to receive the data</returns>
bool app::net::Client::getAll(std::byte * data, int totalBytes)
{
	int bytesReceived = 0;
	while (bytesReceived < totalBytes)
	{
		int retnCheck = SDLNet_TCP_Recv(m_socket, data + bytesReceived, totalBytes - bytesReceived);
		if (retnCheck <= 0)
		{
			return false;
		}
		bytesReceived += retnCheck;
	}

	return true;
}

bool app::net::Client::get(Lobby & _lobby)
{
	int bufferLength;
	if (!get(bufferLength))
	{
		return false;
	}
	auto buffer = std::vector<std::byte>();
	buffer.resize(bufferLength, static_cast<std::byte>('\0'));
	if (!getAll(buffer.data(), bufferLength))
	{
		buffer.clear();
		return false;
	}
	_lobby = *(reinterpret_cast<Lobby *>(buffer.data()));
	buffer.clear();
	return true;
}

bool app::net::Client::get(std::list<Lobby>& _lobbies)
{
	int numberOfLobbies = 0;
	if (!get(numberOfLobbies))
	{
		return false;
	}
	auto lobbies = std::vector<Lobby>();
	lobbies.resize(numberOfLobbies);
	for (auto & lobby : lobbies)
	{
		if (!this->get(lobby))
		{
			return false;
		}
	}
	_lobbies.insert(_lobbies.end()
					, std::make_move_iterator(lobbies.begin())
					, std::make_move_iterator(lobbies.end()));

	return true;
}

/// <summary>
/// Will expect a packet type from server
/// </summary>
/// <param name="_packetType">a packet type to set the received packet to</param>
/// <returns>true if success, false if receive fails</returns>
bool app::net::Client::get(PacketType & _packetType)
{
	if (!getAll((std::byte *)&_packetType, sizeof(PacketType)))
	{
		return false;
	}
	return true;
}

/// <summary>
/// Get an integer from the server
/// </summary>
/// <param name="_int">integer variable to assign</param>
/// <returns>true if success, false if receive fails</returns>
bool app::net::Client::get(int & _int)
{
	if (!getAll((std::byte *)&_int, sizeof(int)))
	{
		return false;
	}
	return true;
}

void app::net::Client::setLobbies(std::list<Lobby>&& lobbies)
{
	m_lobbies.insert(m_lobbies.end()
		, std::make_move_iterator(lobbies.begin())
		, std::make_move_iterator(lobbies.end()));
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










