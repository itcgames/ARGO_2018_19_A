#include "stdafx.h"
#include "Client.h"

void app::net::Client::CloseSocket()
{
	if (SDLNet_TCP_DelSocket(socket_set, socket) == -1)
	{
		app::Console::writeLine({ "ERROR: SDLNet_TCP_DelSocket [", SDLNet_GetError(), "]" });
	}
	SDLNet_FreeSocketSet(socket_set);
	SDLNet_TCP_Close(socket);
}

void app::net::Client::SendData(uint8_t * data, uint16_t length, uint16_t flag)
{
	std::array<std::uint8_t, MAX_PACKET> temp_data;
	memcpy(temp_data.data(), &flag, sizeof(decltype(flag)));
	memcpy(temp_data.data() + sizeof(decltype(flag)), data, length);
	int const offset = sizeof(decltype(flag)) + length;

	int num_sent = SDLNet_TCP_Send(socket, temp_data.data(), offset);
	if (num_sent < offset)
	{
		Console::writeLine({ "ER: SDLNet_TCP_Send: [", SDLNet_GetError(), "]" });
		CloseSocket();
	}
}

uint8_t * app::net::Client::RecvData(uint16_t * length)
{
	app::Console::writeLine("received some data");
	std::array<std::uint8_t, MAX_PACKET> temp_data;
	int num_recv = SDLNet_TCP_Recv(socket, temp_data.data(), MAX_PACKET);
	if (num_recv <= 0)
	{
		CloseSocket();

		const char* err = SDLNet_GetError();
		if (strlen(err) == 0)
		{
			app::Console::writeLine({ "Server shutdown" });
		}
		else
		{
			app::Console::writeLine({ "ERROR: SDLNet_TCP_Recv: [",  SDLNet_GetError(), "]" });
		}
		return NULL;
	}
	else
	{
		*length = num_recv;
		
		uint8_t* data = (uint8_t*)malloc(num_recv * sizeof(uint8_t));
		memcpy(data, temp_data.data(), num_recv);
		return data;
	}
}

void app::net::Client::ProcessData(uint8_t * data, uint16_t * offset)
{
	//dont process if no data
	if (data == NULL) return;

	//get the flag from received buffer
	uint16_t flag = *(uint16_t*) &data[*offset];
	//offset now at start of data stream (size of flag)
	*offset += sizeof(uint16_t);
	 
	//for each flag type
	switch (flag)
	{
		case FLAG_WOOD_UPDATE:
		{
			app::Console::writeLine({ "Wood amount is currently: ", std::to_string(amt_wood) });
			//set wood by accessing data size of wood amount
			amt_wood += *data;
			*offset += sizeof(uint8_t);
			app::Console::writeLine({ "after server update: ", std::to_string(amt_wood) });

		}
		break;
		case FLAG_WOOD_GETTIME:
		{
			//set wood timer by accessing data size of timer
			timer_wood = *(uint32_t*) &data[*offset];
			*offset += sizeof(uint32_t);
		}
		break;
		case FLAG_WOOD_QUEST:
		{
			//NOTE: quest completed
			questing = 0;
		}
		break;
	}
}

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

bool app::net::Client::CheckSocket()
{
	if (SDLNet_CheckSockets(socket_set, 0) == -1)
	{
		app::Console::writeLine({ "ERROR: SDLNet_CheckSockets [", SDLNet_GetError(), "]" });
	}
	return SDLNet_SocketReady(socket);
}

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

bool app::net::Client::sendString(std::string & _string)
{
	auto type = app::net::P_CLIENT_NAME;
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
		//can try add dayta to bytes received
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

bool app::net::Client::processPacket(Packet _packetType)
{
	switch(_packetType)
	{
	case P_CLIENT_NAME:
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








