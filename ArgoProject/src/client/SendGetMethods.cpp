#include "stdafx.h"
#include "client/Client.h"

/// <summary>
/// Extra cpp to contain the send and get methods for the client.
/// </summary>


/// <summary>
/// Send all type of data.
/// </summary>
/// <param name="data">data to send</param>
/// <param name="totalBytes">amount of bytes to send</param>
/// <returns>true if succeeds, false if the sending fails</returns>
bool app::net::Client::sendAll(char * data, int totalBytes)
{

	//Holds the total bytes sent
	int bytesSent = 0;
	//while we still have more bytes to send
	while (bytesSent < totalBytes)
	{
		//try to send remaining bytes
		int RetnCheck = SDLNet_TCP_Send(socket, data + bytesSent, totalBytes - bytesSent);
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
bool app::net::Client::send(std::string & _string, app::net::Packet& _packetType)
{
	app::net::Packet type = _packetType;
	if (!sendPacketType(type))
	{
		return false;
	}
	int bufferLen = _string.size();
	if (!sendInt(bufferLen))
	{
		return false;
	}
	if (!sendAll((char*)_string.c_str(), bufferLen))
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
bool app::net::Client::getString(std::string & _string)
{
	int bufferLength;
	if (!getInt(bufferLength))
	{
		return false;
	}
	char* buffer = new char[bufferLength + 1];
	buffer[bufferLength] = '\0';
	if (!recvAll(buffer, bufferLength))
	{
		delete[] buffer;
		return false;
	}
	_string = buffer;
	delete[] buffer;
	return true;
}


/// <summary>
/// Send the packet type to server
/// </summary>
/// <param name="_packetType">packet type to send</param>
/// <returns>true if succeeds, false if sending fails</returns>
bool app::net::Client::sendPacketType(Packet & _packetType)
{
	if (!sendAll((char*)&_packetType, sizeof(Packet)))
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
bool app::net::Client::sendInt(int _int)
{
	if (!sendAll((char*)&_int, sizeof(int)))
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
bool app::net::Client::recvAll(char * data, int totalBytes)
{
	int bytesReceived = 0;
	while (bytesReceived < totalBytes)
	{
		int retnCheck = SDLNet_TCP_Recv(socket, data + bytesReceived, totalBytes - bytesReceived);
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
bool app::net::Client::getPacketType(Packet & _packetType)
{
	if (!recvAll((char*)&_packetType, sizeof(Packet)))
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
bool app::net::Client::getInt(int & _int)
{
	if (!recvAll((char*)_int, sizeof(int)))
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
		if (!getString(Message))
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
	return false;
}