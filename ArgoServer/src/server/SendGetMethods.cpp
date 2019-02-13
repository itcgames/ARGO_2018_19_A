#include "stdafx.h"
#include "server/Server.h"

/// <summary>
/// This method is used to receive all data,
/// it will keep calling receive until it gets the bytes it expects
/// </summary>
/// <param name="ID">ID of the socket to reveive from</param>
/// <param name="data">the data received from the other socket</param>
/// <param name="totalBytes">total bytes expected to receive from socket</param>
/// <returns>true if succeeds false if SDLNet_TCP_Recv returns error</returns>
bool app::net::Server::recvAll(int ID, char * data, int totalBytes)
{
	int bytesReceived = 0;
	while (bytesReceived < totalBytes)
	{
		int retnCheck = SDLNet_TCP_Recv(sockets[ID], data, totalBytes - bytesReceived);
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
/// <param name="ID">ID of the socket to send to</param>
/// <param name="data">data to send to the socket</param>
/// <param name="totalBytes">total bytes we will send</param>
/// <returns>true if success, false if SDLNet_TCP_Send returns error</returns>
bool app::net::Server::sendAll(int ID, char * data, int totalBytes)
{
	int bytesSent = 0;
	while (bytesSent < totalBytes)
	{
		int retnCheck = SDLNet_TCP_Send(sockets[ID], data + bytesSent, totalBytes - bytesSent);
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
/// <param name="ID">ID of the socket to send to</param>
/// <param name="_int">integer to send</param>
/// <returns>true if success false if sendAll fails</returns>
bool app::net::Server::sendInt(int ID, int _int)
{
	if (!sendAll(ID, (char*)&_int, sizeof(int)))
	{
		return false;
	}
	return true;
}

/// <summary>
/// Await receiving of an integer from another socket.
/// </summary>
/// <param name="ID">ID of the socket to expect and int from</param>
/// <param name="_int">the int to assign received int to</param>
/// <returns>true if success, false if recvAll fails</returns>
bool app::net::Server::getInt(int ID, int & _int)
{
	if (!recvAll(ID, (char*)&_int, sizeof(int)))
	{
		return false;
	}
	return true;
}

/// <summary>
/// Send a packet type to another socket
/// </summary>
/// <param name="ID">ID of the socket to send to</param>
/// <param name="_packetType">packet type to send</param>
/// <returns>true if success, false if sendAll fails</returns>
bool app::net::Server::sendPacketType(int ID, Packet _packetType)
{
	if (!sendAll(ID, (char*)&_packetType, sizeof(Packet)))
	{
		return false;
	}
	return true;
}

/// <summary>
/// Expect a packet type from another socket
/// </summary>
/// <param name="ID">ID of the socket to expect a packet from</param>
/// <param name="_packetType">packet variable to assign the received packet type to</param>
/// <returns>true if success, false if recvAll fails</returns>
bool app::net::Server::getPacketType(int ID, Packet & _packetType)
{
	if (!recvAll(ID, (char*)&_packetType, sizeof(Packet)))
	{
		return false;
	}
	return true;
}

/// <summary>
/// Send a string to a socket.
/// Note the packet passed into this function should be a packet that processes a string ONLY
/// </summary>
/// <param name="ID">ID of the socket to send the string to</param>
/// <param name="_string">string to send</param>
/// <param name="_packetToProcessString">type of packet the other socket is to expect (defines how it will be processed by the other socket)</param>
/// <returns>true if success, false if any of the sends fail</returns>
bool app::net::Server::sendString(int ID, std::string & _string, Packet & _packetToProcessString)
{
	if (!sendPacketType(ID, _packetToProcessString))
	{
		return false;
	}
	int bufferLen = _string.size();
	if (!sendInt(ID, bufferLen))
	{
		return false;
	}
	if (!sendAll(ID, (char*)&_string, sizeof(_string)))
	{
		return false;
	}
	return true;
}

/// <summary>
/// expect string from other socket
/// </summary>
/// <param name="ID">ID of the socket to get string from</param>
/// <param name="_string">string to assign the received string to</param>
/// <returns>true if success, false if any receives fail</returns>
bool app::net::Server::getString(int ID, std::string & _string)
{
	int bufferLength;
	if (!getInt(ID, bufferLength))
	{
		return false;
	}
	char* buffer = new char[bufferLength + 1];
	buffer[bufferLength] = '\0';
	if (!recvAll(ID, buffer, bufferLength))
	{
		delete[] buffer;
		return false;
	}
	_string = buffer;
	delete[] buffer;
	return true;
}

/// <summary>
/// Process the packets that were received
/// </summary>
/// <param name="ID">ID of the socket the packet is from</param>
/// <param name="_packetType">type of packet received</param>
/// <returns>true if successful processing of packet, false if the processing fails</returns>
bool app::net::Server::processPacket(int ID, Packet _packetType)
{
	switch (_packetType)
	{
	case P_CLIENT_NAME_STRING:
	{
		std::string Message;
		if (!getString(ID, Message))
		{
			return false;
		}
		std::cout << Message << std::endl;
		break;
	}
	break;
	default:
		break;
	}
	return true;
}