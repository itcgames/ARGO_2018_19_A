#include "stdafx.h"
#include "server/Server.h"

int main(int argv, char** argc)
{
	app::net::Server server(27000);
	while (true)
	{
		server.listenForSockets();
	}

	return EXIT_SUCCESS;
}
