#ifndef _CLIENT_H
#define _CLIENT_H
#include"stdafx.h"

namespace app::net
{

	enum Packet {
		P_CLIENT_NAME
	};
	class Client
	{
	public: // Constructors/Destructor/Assignments
		Client() = default;
		~Client() = default;

		Client(Client const &) = default;
		Client & operator=(Client const &) = default;

		Client(Client &&) = default;
		Client & operator=(Client &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		void CloseSocket();
		void SendData(uint8_t* data, uint16_t length, uint16_t flag);
		uint8_t* RecvData(uint16_t* length);
		void ProcessData(uint8_t* data, uint16_t* offset);
		bool InitNetwork(std::string const & pIP, int iPort);
		bool CheckSocket();
		bool sendAll(char* data, int totalBytes);
		bool sendString(std::string& _string);
		bool getString(std::string& _string);
		bool sendPacketType(Packet& _packetType);
		bool sendInt(int _int);
		bool recvAll(char * data, int totalBytes);
		bool getPacketType(Packet& _packetType);
		bool getInt(int& _int);
		bool processPacket(Packet _packetType);
		
	public: // Public Static Variables
		static constexpr int MAX_PACKET = 255;
		static constexpr int FLAG_QUIT = 0;
		static constexpr int FLAG_WOOD_QUEST = 17;
		static constexpr int FLAG_WOOD_UPDATE = 16;
		static constexpr int FLAG_WOOD_GETTIME = 18;
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables


		TCPsocket socket;
		SDLNet_SocketSet socket_set;

		int questing;
		uint8_t amt_wood;
		uint32_t timer_wood;
	};
}

#endif // !_CLIENT_H
