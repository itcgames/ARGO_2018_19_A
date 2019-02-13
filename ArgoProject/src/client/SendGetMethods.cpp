#include "stdafx.h"
#include "client/Client.h"

/// <summary>
/// Extra cpp to contain the send and get methods for the client.
/// </summary>

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

bool app::net::Client::sendString(std::string & _string, app::net::Packet& _packetToProcessString)
{
	app::net::Packet type = _packetToProcessString;
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



bool app::net::Client::sendPacketType(Packet & _packetType)
{
	if (!sendAll((char*)&_packetType, sizeof(Packet)))
	{
		return false;
	}
	return true;
}

bool app::net::Client::sendInt(int _int)
{
	if (!sendAll((char*)&_int, sizeof(int)))
	{
		return false;
	}
	return true;
}

bool app::net::Client::recvAll(char * data, int totalBytes)
{
	int bytesReceived = 0;
	while (bytesReceived < totalBytes)
	{
		int retnCheck = SDLNet_TCP_Recv(socket, data + bytesReceived, totalBytes - bytesReceived);
		//can try add data to bytes received
		if (retnCheck <= 0)
		{
			return false;
		}
		bytesReceived += retnCheck;
	}

	return true;
}

bool app::net::Client::getPacketType(Packet & _packetType)
{
	if (!recvAll((char*)&_packetType, sizeof(Packet)))
	{
		return false;
	}
	return true;
}

bool app::net::Client::getInt(int & _int)
{
	if (!recvAll((char*)_int, sizeof(int)))
	{
		return false;
	}
	return true;
}

bool app::net::Client::sendPlayerName(std::string _name)
{

	return false;
}

bool app::net::Client::processPacket(Packet _packetType)
{
	switch (_packetType)
	{
	case P_CLIENT_NAME_STRING:
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