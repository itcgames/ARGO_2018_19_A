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
void app::net::Server::listenForSockets()
{
	//main processing loop
	int running = 1;
	while (running)
	{
		int num_rdy = SDLNet_CheckSockets(socket_set, 1000);
		if (num_rdy <= 0)
		{
			//NOTE: none of the sockets are ready.
		}
		else
		{
			//NOTE: some number of sockets are ready.
			if (SDLNet_SocketReady(server_socket))
			{
				int got_socket = acceptSocket(next_ind);
				if (!got_socket)
				{
					num_rdy--;
					continue;
				}
				//NOTE: get a new index.
				int chk_count;
				for (chk_count = 0; chk_count < MAX_SOCKETS; ++chk_count)
				{
					if (sockets[(next_ind + chk_count) % MAX_SOCKETS] == NULL) break;
				}
				next_ind = (next_ind + chk_count) % MAX_SOCKETS;
				app::Console::writeLine({ "new connection, next_ind: ", std::to_string(next_ind) });
				num_rdy--;
			}
			Packet packetType;

			for (int ind = 0; ind < MAX_SOCKETS; ++ind)
			{
				if (sockets[ind] == NULL) continue;

				if (!getPacketType(ind, packetType))
				{
					app::Console::writeLine("could not get packet type");
				}
				if (!processPacket(ind, packetType))
				{
					app::Console::writeLine("cold not send packet type");
				}
			}
		}
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
}

/// <summary>
/// This function will accept a socket trying to connect
/// </summary>
/// <param name="index">index of the socket</param>
/// <returns>whether or not connection is successful</returns>
int app::net::Server::acceptSocket(int index)
{
	if (sockets[index])
	{
		app::Console::writeLine({ "Overriding a socket at index: ", std::to_string(index) });
	}

	sockets[index] = SDLNet_TCP_Accept(server_socket);
	if (sockets[index] == NULL) return 0;

	if (SDLNet_TCP_AddSocket(socket_set, sockets[index]) == -1)
	{
		app::Console::writeLine({ "ERROR: SDLNet_TCP_AddSocket [", SDLNet_GetError(), "]" });
	}
	return 1;
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
