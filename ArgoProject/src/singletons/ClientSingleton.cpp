#include "stdafx.h"
#include "ClientSingleton.h"

std::unique_ptr<app::net::Client> app::sin::Client::s_client = nullptr;

app::net::Client & app::sin::Client::get()
{
	if (!s_client)
	{
		s_client = std::make_unique<app::net::Client>();
	}
	return *s_client;
}
