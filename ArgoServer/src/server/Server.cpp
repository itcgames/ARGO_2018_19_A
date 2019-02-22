#include "stdafx.h"
#include "Server.h"

/// <summary>
/// Constructor for server,
/// will call initialization of server
/// </summary>
/// <param name="_port">port to open the server on</param>
app::net::Server::Server(int _port)
	: m_clientThreads()
	, m_serverSocket(NULL)
	, m_socketSet(NULL)
	, m_sockets()
	, m_totalConnections(0)
	, m_lobbies()
{
	m_sockets.fill(NULL);
	initServer(_port);
}

app::net::Server::~Server()
{
	this->sdlCleanup();
}

/// <summary>
/// Method will listen for sockets connecting as well as check if any sockets sent anything.
/// 
/// </summary>
bool app::net::Server::listenForSockets()
{
	bool got_socket = acceptSocket(m_freeSocket);
	if (!got_socket)
	{
		//app::Console::writeLine({ "Failed to accept the clients connection" });
		return false;
	}
	else
	{
		app::Console::writeLine({ "Client connected! ID: ", std::to_string(m_freeSocket) });
		if (auto const & foundClient = m_clientThreads.find(m_freeSocket); foundClient != m_clientThreads.end())
		{
			// Client is already in the map
			auto &[thread, stopThread] = foundClient->second;
			if (thread.has_value())
			{
				if (thread->joinable()) { stopThread.store(true); thread->join(); }
				stopThread.store(false);
				thread.reset();
			}
			thread = std::thread(&app::net::Server::clientHandlerThread, this, m_freeSocket, std::ref(stopThread));
		}
		else
		{
			// Client is not in the map
			m_clientThreads.insert(std::make_pair(m_freeSocket, std::make_pair(std::nullopt, false)));
			auto &[thread, stopThread] = m_clientThreads.at(m_freeSocket);
			thread = std::thread(&app::net::Server::clientHandlerThread, this, m_freeSocket, std::ref(stopThread));
		}
		m_freeSocket = this->getFreeSocket(m_freeSocket);
		++m_totalConnections;
		return true;
	}
}


/// <summary>
/// Method to initialize the server.
/// creates server at passed port
/// </summary>
/// <param name="_port">port to connect to</param>
void app::net::Server::initServer(int _port)
{
	//Initialize SDL stuff
	if (SDL_Init(SDL_INIT_EVERYTHING) != NULL)
	{
		app::Console::writeLine({ "ERROR: Initializing SDL [", SDL_GetError(), "]" });
	}
	if (SDLNet_Init() != NULL)
	{
		app::Console::writeLine({ "ERROR: Initializing SDLNet [", SDLNet_GetError(), "]" });
	}

	//start up the server
	IPaddress ip;
	//attempt to resolve the host
	if (SDLNet_ResolveHost(&ip, NULL, 27000) == -1)
	{
		app::Console::writeLine({ "ERROR: SDLNet_ResolveHost: [", SDLNet_GetError(), "]" });
		exit(EXIT_FAILURE);
	}
	if (SDLNet_ResolveIP(&ip) == NULL) {
		printf("SDLNet_ResolveIP: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

	outputIP(ip);

	//open the servers socket
	m_serverSocket = SDLNet_TCP_Open(&ip);
	if (m_serverSocket == NULL)
	{
		app::Console::writeLine({ "ERROR: SDL_Net_TCP_Open: [", SDLNet_GetError(), "]" });
	}
	//set and add server socket to socket set (+1 to account for server socket).
	m_socketSet = SDLNet_AllocSocketSet(s_MAX_SOCKETS + 1);
	if (m_socketSet == NULL)
	{
		app::Console::writeLine({ "ERROR: SDLNet_AllocSocketSet [", SDLNet_GetError(), "]" });
	}
	if (SDLNet_TCP_AddSocket(m_socketSet, m_serverSocket) == -1)
	{
		app::Console::writeLine({ "ERROR: SDLNet_TCP_AddSocket [" , SDLNet_GetError(), "]" });
	}
}

/// <summary>
/// This function will accept a socket trying to connect
/// </summary>
/// <param name="index">index of the socket</param>
/// <returns>true if accepted successfully, false if unsuccessful</returns>
bool app::net::Server::acceptSocket(int index)
{
	auto & socket = m_sockets.at(index);
	if (socket)
	{
		app::Console::writeLine({ "Overriding a socket at index: ", std::to_string(index) });
	}

	socket = SDLNet_TCP_Accept(m_serverSocket);
	if (socket == NULL) return false;

	if (SDLNet_TCP_AddSocket(m_socketSet, socket) == -1)
	{
		app::Console::writeLine({ "ERROR: SDLNet_TCP_AddSocket [", SDLNet_GetError(), "]" });
	}
	return true;
}

/// <summary>
/// Close socket at index that is passed in.
/// </summary>
/// <param name="index">index at which socket we want to close in is</param>
void app::net::Server::closeSocket(int index)
{
	auto & socket = m_sockets.at(index);
	if (socket == NULL)
	{
		app::Console::writeLine({ "ERROR: Attempted to delete a NULL socket." });
		return;
	}
	if (SDLNet_TCP_DelSocket(m_socketSet, socket) == -1)
	{
		app::Console::writeLine({ "ERROR: SDLNet_TCP_DelSocket: [", SDLNet_GetError(), "]" });
	}
	SDLNet_TCP_Close(socket);
	socket = NULL;
	m_freeSocket = this->getFreeSocket(static_cast<std::uint8_t>(index));
	--m_totalConnections;
}

/// <summary>
/// Clean up the SDL stuff when done
/// </summary>
void app::net::Server::sdlCleanup()
{
	for (auto &[id, mapValue] : m_clientThreads)
	{
		auto &[thread, stopThreadBool] = mapValue;
		if (thread.has_value())
		{
			stopThreadBool.store(true);
			if (thread->joinable()) { thread->join(); }
			thread.reset();
		}
	}

	//clean up everything when server is done.
	if (SDLNet_TCP_DelSocket(m_socketSet, m_serverSocket) == -1)
	{
		app::Console::writeLine({ "ERROR: SDLNet_TCP_DelSocket: [", SDLNet_GetError(), "]" });
	}
	SDLNet_TCP_Close(m_serverSocket);

	for (int i = 0; i < s_MAX_SOCKETS; ++i)
	{
		if (m_sockets.at(i) == NULL) continue;
		closeSocket(i);
	}

	SDLNet_FreeSocketSet(m_socketSet);
	SDLNet_Quit();
	SDL_Quit();
}

std::uint8_t app::net::Server::getFreeSocket(std::uint8_t startIndex) const
{
	constexpr auto size = static_cast<std::uint8_t>(s_MAX_SOCKETS);
	if (startIndex >= size) { startIndex = 0; }
	const std::uint8_t startingLocation = startIndex;
	while (m_sockets.at(startIndex) != NULL)
	{
		if (startIndex < size) { ++startIndex; }
		else { startIndex = 0; }
		if (startingLocation == startIndex) { break; }
	}
	return startIndex;
}

/// <summary>
/// Spin up a thread that will handle receiving and sending of packets.
/// </summary>
/// <param name="ID"></param>
void app::net::Server::clientHandlerThread(int id, std::atomic<bool> & stopThread)
{
	PacketType packetType = PacketType::UNKNOWN;

	while (!stopThread.load())
	{
		if (!this->get(id, packetType))
		{
			break;
		}
		if (!this->processPacket(id, packetType))
		{
			break;
		}
	}
	this->output(id, "Stopped connection");
	this->closeSocket(id);
}

/// <summary>
/// This method is used to receive all data,
/// it will keep calling receive until it gets the bytes it expects
/// </summary>
/// <param name="id">id of the socket to reveive from</param>
/// <param name="data">the data received from the other socket</param>
/// <param name="totalBytes">total bytes expected to receive from socket</param>
/// <returns>true if succeeds false if SDLNet_TCP_Recv returns error</returns>
bool app::net::Server::getAll(int id, std::byte * data, int totalBytes)
{
	int bytesReceived = 0;
	while (bytesReceived < totalBytes)
	{
		int retnCheck = SDLNet_TCP_Recv(m_sockets[id], data, totalBytes - bytesReceived);
		if (retnCheck <= 0)
		{
			return false;
		}
		bytesReceived += retnCheck;
	}
	return true;
}

/// <summary>
/// Send any type of data, it will call the send while there are still bytes to be sent.
/// </summary>
/// <param name="id">id of the socket to send to</param>
/// <param name="data">data to send to the socket</param>
/// <param name="totalBytes">total bytes we will send</param>
/// <returns>true if success, false if SDLNet_TCP_Send returns error</returns>
bool app::net::Server::sendAll(int id, std::byte * data, int totalBytes)
{
	int bytesSent = 0;
	while (bytesSent < totalBytes)
	{
		int retnCheck = SDLNet_TCP_Send(m_sockets[id], data + bytesSent, totalBytes - bytesSent);
		if (retnCheck < bytesSent)
		{
			return false;
		}
		bytesSent += retnCheck;
	}
	return true;
}

/// <summary>
/// Send an integer to another socket
/// </summary>
/// <param name="id">id of the socket to send to</param>
/// <param name="_int">integer to send</param>
/// <returns>true if success false if sendAll fails</returns>
bool app::net::Server::send(int id, const int& _int)
{
	if (!sendAll(id, (std::byte *)&_int, sizeof(int)))
	{
		return false;
	}
	return true;
}

/// <summary>
/// Await receiving of an integer from another socket.
/// </summary>
/// <param name="id">id of the socket to expect and int from</param>
/// <param name="_int">the int to assign received int to</param>
/// <returns>true if success, false if recvAll fails</returns>
bool app::net::Server::get(int id, int & _int)
{
	if (!getAll(id, (std::byte *)&_int, sizeof(int)))
	{
		return false;
	}
	return true;
}

/// <summary>
/// Send a packet type to another socket
/// </summary>
/// <param name="id">id of the socket to send to</param>
/// <param name="_packetType">packet type to send</param>
/// <returns>true if success, false if sendAll fails</returns>
bool app::net::Server::send(int id, const PacketType& _packetType)
{
	if (!sendAll(id, (std::byte *)&_packetType, sizeof(PacketType)))
	{
		return false;
	}
	return true;
}

/// <summary>
/// Expect a packet type from another socket
/// </summary>
/// <param name="id">id of the socket to expect a packet from</param>
/// <param name="_packetType">packet variable to assign the received packet type to</param>
/// <returns>true if success, false if recvAll fails</returns>
bool app::net::Server::get(int id, PacketType & _packetType)
{
	if (!getAll(id, (std::byte *)&_packetType, sizeof(PacketType)))
	{
		return false;
	}
	return true;
}

/// <summary>
/// Send a string to a socket.
/// Note the packet passed into this function should be a packet that processes a string ONLY
/// </summary>
/// <param name="id">id of the socket to send the string to</param>
/// <param name="_string">string to send</param>
/// <param name="_packetType">type of packet the other socket is to expect (defines how it will be processed by the other socket)</param>
/// <returns>true if success, false if any of the sends fail</returns>
bool app::net::Server::send(int id, const std::string & _string, const PacketType & _packetType)
{
	if (!send(id, _packetType))
	{
		return false;
	}
	int bufferLen = _string.size();
	if (!send(id, bufferLen))
	{
		return false;
	}
	if (!sendAll(id, (std::byte *)&_string, sizeof(_string)))
	{
		return false;
	}
	return true;
}

bool app::net::Server::send(int id, Lobby const & _lobby)
{
	constexpr auto BUFFER_SIZE = sizeof(Lobby);
	return send(id, BUFFER_SIZE) && sendAll(id, (std::byte *)&_lobby, BUFFER_SIZE);
}


/// <summary>
/// expect string from other socket
/// </summary>
/// <param name="id">id of the socket to get string from</param>
/// <param name="_string">string to assign the received string to</param>
/// <returns>true if success, false if any receives fail</returns>
bool app::net::Server::get(int id, std::string & _string)
{
	int bufferLength;
	if (!get(id, bufferLength))
	{
		return false;
	}
	auto buffer = std::vector<std::byte>();
	buffer.resize(bufferLength, static_cast<std::byte>('\0'));
	if (!getAll(id, buffer.data(), bufferLength))
	{
		buffer.clear();
		return false;
	}
	_string.reserve(buffer.size());
	_string.insert(_string.begin()
				   , std::make_move_iterator(buffer.begin())
				   , std::make_move_iterator(buffer.end()));
	buffer.clear();
	return true;
}

/// <summary>
/// Process the packets that were received
/// </summary>
/// <param name="id">id of the socket the packet is from</param>
/// <param name="_packetType">type of packet received</param>
/// <returns>true if successful processing of packet, false if the processing fails</returns>
bool app::net::Server::processPacket(int id, PacketType _packetType)
{
	switch (_packetType)
	{
		case PacketType::CLIENT_NAME:
			return this->processClientName(id);
		case PacketType::LOBBY_CREATE:
			return this->processLobbyCreate(id);
		case PacketType::LOBBY_GET_ALL:
			return this->processLobbyGetAll(id);
		case PacketType::UNKNOWN:
		default:
			return this->processDefault(id);
	}
}

bool app::net::Server::processClientName(int id)
{
	auto clientName = std::string();
	if (!get(id, clientName))
	{
		return false;
	}
	this->output(id, { "Received name '", clientName, "'" });
	return true;
}

bool app::net::Server::processLobbyCreate(int id)
{
	//handle creation of a lobby
	auto playerName = std::string();
	playerName.reserve(20);
	if (!get(id, playerName))
	{
		return false;
	}
	m_lobbies.push_back(Lobby());
	auto & lobby = m_lobbies.back();
	lobby.setName(playerName + "'s Lobby");
	lobby.addPlayer(id, playerName);
	this->output(id, { "Created a lobby with name: \"", lobby.getName(), "\"" });

	//send out lobby created message to everyone else
	constexpr auto PACKET_TYPE = app::net::PacketType::LOBBY_WAS_CREATED;
	for (int i = 0; i < m_totalConnections; i++)
	{
		if (i == id) { continue; }
		//send the vector of servers to client whenever a new server is added or just send a single lobby that was added.
		if (!this->send(i, PACKET_TYPE) || !this->send(i, lobby))
		{
			this->output(id, { "Send Lobby[", lobby.getName(), "] to player[", std::to_string(i), "]" });
		}
		else
		{
			break;
		}
	}
	return true;
}

bool app::net::Server::processLobbyGetAll(int id)
{
	// Request to get all the lobbies has been sent
	if (!send(id, m_lobbies.size()))
	{
		return false;
	}
	for (auto const & lobby : m_lobbies)
	{
		if (!send(id, lobby))
		{
			return false;
		}
	}
	return true;
}

bool app::net::Server::processDefault(int id)
{
	this->output(id, "No processing done for this packet type");
	return false;
}

void app::net::Server::outputIP(IPaddress const & ip)
{
	// Get our IP address in proper dot-quad format by breaking up the 32-bit unsigned host address and splitting it into an array of four 8-bit unsigned numbers...
	std::uint8_t const * dotQuad = reinterpret_cast<std::uint8_t const *>(&ip.host);
	
	auto const & toString = [](std::uint8_t const & num) { return std::to_string(static_cast<std::uint16_t>(num)); };
	//std::uint16_t
	//... and then outputting them cast to integers. Then read the last 16 bits of the serverIP object to get the port number
	app::Console::write({ "Successfully resolved server host to IP: ", toString(dotQuad[0]), ".", toString(dotQuad[1]), ".", toString(dotQuad[2]), ".", toString(dotQuad[3]) });
	app::Console::writeLine({ " port ", std::to_string(SDLNet_Read16(&ip.port)) });
	app::Console::writeLine();
}

void app::net::Server::output(int id, std::string const & msg) const
{
	if constexpr (s_DEBUG_MODE)
	{
		app::Console::writeLine({ "ID[", std::to_string(id), "]: ", msg });
	}
}

void app::net::Server::output(int id, std::initializer_list<std::string> const & msgs) const
{
	if constexpr (s_DEBUG_MODE)
	{
		app::Console::write({ "ID[", std::to_string(id), "]: " });
		app::Console::writeLine(msgs);
	}
}




