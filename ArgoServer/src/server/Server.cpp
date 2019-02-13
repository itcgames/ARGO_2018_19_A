#include "stdafx.h"
#include "Server.h"

/// <summary>
/// Constructor for server,
/// will call initialization of server
/// </summary>
/// <param name="_port">port to open the server on</param>
app::net::Server::Server(int _port)
{
	initServer(_port);
}

/// <summary>
/// Method will listen for sockets connecting as well as check if any sockets sent anything.
/// 
/// </summary>
bool app::net::Server::listenForSockets()
{
	bool got_socket = acceptSocket(totalConnections);
	if (!got_socket)
	{
		//app::Console::writeLine({ "Failed to accept the clients connection" });
		return false;
	}
	else
	{
		app::Console::writeLine({ "Client connected! ID: ", std::to_string(totalConnections) });
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)clientHandlerThread, (LPVOID)(totalConnections), NULL, NULL);
		totalConnections += 1;
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
		exit(1);
	}
	// Get our IP address in proper dot-quad format by breaking up the 32-bit unsigned host address and splitting it into an array of four 8-bit unsigned numbers...
	Uint8 * dotQuad = (Uint8*)&ip.host;

	//... and then outputting them cast to integers. Then read the last 16 bits of the serverIP object to get the port number
	std::cout << "Successfully resolved server host to IP: " << (unsigned short)dotQuad[0] << "." << (unsigned short)dotQuad[1] << "." << (unsigned short)dotQuad[2] << "." << (unsigned short)dotQuad[3];
	std::cout << " port " << SDLNet_Read16(&ip.port) << std::endl << std::endl;

	//open the servers socket
	server_socket = SDLNet_TCP_Open(&ip);
	if (server_socket == NULL)
	{
		app::Console::writeLine({ "ERROR: SDL_Net_TCP_Open: [", SDLNet_GetError(), "]" });
	}
	//set and add server socket to socket set (+1 to account for server socket).
	socket_set = SDLNet_AllocSocketSet(MAX_SOCKETS + 1);
	if (socket_set == NULL)
	{
		app::Console::writeLine({ "ERROR: SDLNet_AllocSocketSet [", SDLNet_GetError(), "]" });
	}
	if (SDLNet_TCP_AddSocket(socket_set, server_socket) == -1)
	{
		app::Console::writeLine({ "ERROR: SDLNet_TCP_AddSocket [" , SDLNet_GetError(), "]" });
	}
	serverptr = this;
}

/// <summary>
/// This function will accept a socket trying to connect
/// </summary>
/// <param name="index">index of the socket</param>
/// <returns>true if accepted successfully, false if unsuccessful</returns>
bool app::net::Server::acceptSocket(int index)
{
	if (sockets[index])
	{
		app::Console::writeLine({ "Overriding a socket at index: ", std::to_string(index) });
	}

	sockets[index] = SDLNet_TCP_Accept(server_socket);
	if (sockets[index] == NULL) return false;

	if (SDLNet_TCP_AddSocket(socket_set, sockets[index]) == -1)
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
	if (sockets[index] == NULL)
	{
		app::Console::writeLine({ "ERROR: Attempted to delete a NULL socket." });
		return;
	}
	if (SDLNet_TCP_DelSocket(socket_set, sockets[index]) == -1)
	{
		app::Console::writeLine({ "ERROR: SDLNet_TCP_DelSocket: [", SDLNet_GetError(), "]" });
	}
	SDLNet_TCP_Close(sockets[index]);
	sockets[index] = NULL;
}

/// <summary>
/// Clean up the SDL stuff when done
/// </summary>
void app::net::Server::sdlCleanup()
{
	//clean up everything when server is done.
	if (SDLNet_TCP_DelSocket(socket_set, server_socket) == -1)
	{
		app::Console::writeLine({ "ERROR: SDLNet_TCP_DelSocket: [", SDLNet_GetError(), "]" });
	}
	SDLNet_TCP_Close(server_socket);

	for (int i = 0; i < MAX_SOCKETS; ++i)
	{
		if (sockets[i] == NULL) continue;
		closeSocket(i);
	}

	SDLNet_FreeSocketSet(socket_set);
	SDLNet_Quit();
	SDL_Quit();
}

/// <summary>
/// Spin up a thread that will handle receiving and sending of packets.
/// </summary>
/// <param name="ID"></param>
void app::net::Server::clientHandlerThread(int ID)
{
	Packet packetType;

	while (true)
	{
		if (!serverptr->getPacketType(ID, packetType))
		{
			break;
		}
		if (!serverptr->processPacket(ID, packetType))
		{
			break;
		}
	}
	app::Console::writeLine({ "Lost connection to client ID: ", std::to_string(ID) });
	serverptr->closeSocket(ID);
	return;
}



