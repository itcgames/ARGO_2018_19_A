#include "stdafx.h"
#include "Server.h"

/// <summary>
/// Constructor for server,
/// will call initialization of server
/// </summary>
/// <param name="_port">port to open the server on</param>
app::net::Server::Server(int _port)
	: PacketParser()
	, m_clientThreads()
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
	auto ip = IPaddress();
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
	if (!this->send(index, index))
	{
		app::Console::writeLine({ "ERROR: Failed to send the new clients id[", index, "]" });
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
	auto const predicate = [&](Lobby::Player const & player) { return player.has_value() && player->first == index; };
	for (auto & lobby : m_lobbies)
	{
		auto & players = lobby.getPlayers();
		if (auto const & result = std::find_if(players.begin(), players.end(), predicate); result != players.end())
		{
			this->output(index, { "Removed from lobby[", lobby.getId(), "] \"", lobby.getName(), "\"" });
			result->reset();
		}
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
		if (!this->get(id, packetType)) { break; }
		if (!this->processPacket(id, packetType)) { break; }
	}
	this->output(id, "Stopped connection");
	this->closeSocket(id);
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
		case PacketType::LOBBY_JOINED:
			return this->processLobbyJoined(id);
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
	if (!this->get(id, playerName)) { return false; }

	m_lobbies.push_back(Lobby());
	auto & lobby = m_lobbies.back();
	lobby.setName(playerName + "'s Lobby");
	lobby.setId(m_idGenerator++);
	this->output(id, { "Created a lobby with name: \"", lobby.getName(), "\"" });

	//send out lobby created message to everyone
	constexpr auto PACKET_TYPE = app::net::PacketType::LOBBY_WAS_CREATED;
	for (std::size_t i = 0; i < m_sockets.size(); i++)
	{
		if (m_sockets.at(i) == NULL) { continue; }
		// send the lobby that was added and its creator.

		if (this->send(static_cast<int>(i), PACKET_TYPE) && this->send(static_cast<int>(i), lobby))
		{
			if (i == id)
			{
				if (this->send(static_cast<int>(i), id))
				{
					this->output(id, { "Send Lobby[", lobby.getName(), "] to the creator player[", i, "]" });
				}
				else
				{
					this->output(id, { "Failed to send Lobby[", lobby.getName(), "] to the creator player[", i, "]" });
				}
			}
			else
			{
				this->output(id, { "Send Lobby[", lobby.getName(), "] to player[", i, "]" });
			}
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
	if (!this->send(id, m_lobbies.size())) { return false; }

	for (auto const & lobby : m_lobbies)
	{
		if (!this->send(id, lobby)) { return false; }
	}
	return true;
}

bool app::net::Server::processLobbyJoined(int id)
{
	auto lobbyId = std::uint8_t();
	if (!this->get(id, lobbyId)) { return false; }

	auto const & predicate = [&lobbyId](app::net::Lobby const & lobby) { return lobby.getId() == lobbyId; };
	if (auto const & lobbyResult = std::find_if(m_lobbies.begin(), m_lobbies.end(), predicate); lobbyResult != m_lobbies.end())
	{
		auto & lobby = *lobbyResult;
		auto playerName = std::string();
		if (!this->get(id, playerName)) { return false; }
		if (auto const & addResult = lobby.addPlayer(id, playerName); addResult.has_value())
		{
			if (!this->send(id, addResult.value())) { return false; }
			this->output(id, { "Player joined lobby[", lobby.getId(), "] in slot[", addResult.value(), "]" });

			auto lobbyPlayers = std::vector<app::net::Lobby::Player::value_type>();
			for (auto const & player : lobby.getPlayers())
			{
				if (player.has_value()) { lobbyPlayers.push_back(player.value()); }
			}
			for (auto const &[playerId, name] : lobbyPlayers)
			{
				if (playerId == id)
				{
					constexpr auto PACKET_TYPE = PacketType::LOBBY_JOINED_MY;
					if (!this->send(id, PACKET_TYPE)) { return false; }
					if (!this->send(playerId, lobby)) { return false; }
				}
			}
			for (std::size_t i = 0; i < m_sockets.size(); ++i)
			{
				if (m_sockets.at(i) == NULL || i == id) { continue; }

				constexpr auto PACKET_TYPE = PacketType::LOBBY_JOINED;
				if (!this->send(i, PACKET_TYPE)) { return false; }
				if (!this->send(i, lobby)) { return false; }
			}
		}
		else
		{
			this->output(id, { "Player failed to join lobby[", lobby.getId(), "]" });
		}
	}
	else
	{
		this->output(id, { "Failed to find lobby with id[", lobbyId, "]" });
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
	auto ipString = std::stringstream();

	// Construst our IP Address string
	// reading the Ip from the way SDL stores it (keeps all the numbers packed into 32 bits)
	// Get our IP address in proper dot-quad format by breaking up the 32-bit unsigned host address and splitting it into an array of four 8-bit unsigned numbers...
	std::uint8_t const * itt = reinterpret_cast<std::uint8_t const *>(&ip.host);
	std::uint8_t const * end = itt + (sizeof(std::uint8_t) * 4); // NOTE: end being one past the end is intentional
	std::string separator = "";
	for (; itt != end; itt += sizeof(std::uint8_t))
	{
		ipString << separator << std::to_string(static_cast<std::uint16_t>(*itt));
		if (separator != ".") { separator = "."; }
	}
	

	//... and then outputting them cast to integers. Then read the last 16 bits of the serverIP object to get the port number
	app::Console::write({ "Successfully resolved host to IP: ", ipString.str() });
	app::Console::writeLine({ " port: ", std::to_string(SDLNet_Read16(&ip.port)) });
	//std::uint16_t
	app::Console::writeLine();
}

void app::net::Server::output(int id, std::string const & msg) const
{
	if constexpr (s_DEBUG_MODE)
	{
		app::Console::writeLine({ "ID[", std::to_string(id), "]: ", msg });
	}
}

void app::net::Server::output(int id, std::initializer_list<app::Console::Variant> const & msgs) const
{
	if constexpr (s_DEBUG_MODE)
	{
		app::Console::write({ "ID[", std::to_string(id), "]: " });
		app::Console::writeLine(msgs);
	}
}
