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
	m_socket = SDLNet_TCP_Open(&ip);
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
		app::Console::writeLine({ "ERROR: SDLNet_CheckSockets [", SDLNet_GetError(), "]" });
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
bool app::net::Client::send(const std::string & _string, const app::net::Packet& _packetType)
{
	app::net::Packet type = _packetType;
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
bool app::net::Client::send(const Packet& _packetType)
{
	if (!sendAll((std::byte *)&_packetType, sizeof(Packet)))
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

/// <summary>
/// Will expect a packet type from server
/// </summary>
/// <param name="_packetType">a packet type to set the received packet to</param>
/// <returns>true if success, false if receive fails</returns>
bool app::net::Client::get(Packet & _packetType)
{
	if (!getAll((std::byte *)&_packetType, sizeof(Packet)))
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
	if (!getAll((std::byte *)_int, sizeof(int)))
	{
		return false;
	}
	return true;
}

/// <summary>
/// Process a packet based on the type of packet received.
/// </summary>
/// <param name="_packetType">type of received packet</param>
/// <returns>true if processes successfuly, false if fails processing</returns>
bool app::net::Client::processPacket(Packet _packetType)
{
	switch (_packetType)
	{
	case Packet::CLIENT_NAME:
	{
		std::string Message;
		if (!get(Message))
		{
			return false;
		}
		if constexpr (s_DEBUG_MODE)
		{
			app::Console::writeLine(Message);
		}
		break;
	}
	case Packet::LOBBY_CREATE:
	{

	} break;
	default:
		break;
	}
	return false;
}










