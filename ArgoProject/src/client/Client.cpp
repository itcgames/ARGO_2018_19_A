#include "stdafx.h"
#include "Client.h"

/// <summary>
/// This function will close the socket.
/// </summary>
void app::net::Client::CloseSocket()
{
	if (SDLNet_TCP_DelSocket(socket_set, socket) == -1)
	{
		app::Console::writeLine({ "ERROR: SDLNet_TCP_DelSocket [", SDLNet_GetError(), "]" });
	}
	SDLNet_FreeSocketSet(socket_set);
	SDLNet_TCP_Close(socket);
}

/// <summary>
/// Initialize the network, attempt to connect to server
/// </summary>
/// <param name="pIP">Ip to connect to</param>
/// <param name="iPort">port to connect through</param>
/// <returns>true if success, false if connection cant be established</returns>
bool app::net::Client::InitNetwork(std::string const & pIP, int iPort)
{
	socket_set = SDLNet_AllocSocketSet(1);



	IPaddress ip;
	if (SDLNet_ResolveHost(&ip, pIP.c_str(), iPort) != NULL);
	{
		app::Console::writeLine({ "ERROR: SDLNet_ResolveHost: [", SDLNet_GetError(), "]" });
	}
	// Get our IP address in proper dot-quad format by breaking up the 32-bit unsigned host address and splitting it into an array of four 8-bit unsigned numbers...
	Uint8 * dotQuad = (Uint8*)&ip.host;
	//... and then outputting them cast to integers. Then read the last 16 bits of the serverIP object to get the port number
	std::cout << "Successfully resolved server host to IP: " << (unsigned short)dotQuad[0] << "." << (unsigned short)dotQuad[1] << "." << (unsigned short)dotQuad[2] << "." << (unsigned short)dotQuad[3];
	std::cout << " port " << SDLNet_Read16(&ip.port) << std::endl << std::endl;
	
	//open the servers socket
	socket = SDLNet_TCP_Open(&ip);
	if (socket == NULL)
	{
		app::Console::writeLine({ "ERROR: SDLNer_TCP_Open: [", SDLNet_GetError(), "]" });
		return false;
	}

	if (SDLNet_TCP_AddSocket(socket_set, socket) == -1)
	{
		app::Console::writeLine({ "ERROR: SDLNet_TCP_AddSocket: [", SDLNet_GetError(), "]" });
		return false;
	}

	return true;
}

/// <summary>
/// Check if the socket is ready to send/receive data
/// </summary>
/// <returns></returns>
bool app::net::Client::CheckSocket()
{
	if (SDLNet_CheckSockets(socket_set, 0) == -1)
	{
		app::Console::writeLine({ "ERROR: SDLNet_CheckSockets [", SDLNet_GetError(), "]" });
	}
	return SDLNet_SocketReady(socket);
}










