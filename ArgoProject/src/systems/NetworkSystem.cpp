#include "stdafx.h"
#include "NetworkSystem.h"
#include "singletons/ClientSingleton.h"

app::sys::NetworkSystem::NetworkSystem()
	: BaseSystem()
	, m_client(app::sin::Client::get())
	, m_packetType()
{
	m_client.initNetwork(s_SERVER_IP, s_SERVER_PORT);
}

void app::sys::NetworkSystem::update(app::time::seconds const & dt)
{
	if (m_client.checkSocket())
	{
		m_packetType = app::net::Packet::UNKNOWN;
		if (!m_client.get(m_packetType))
		{
			this->output("Failed to retrieve packet type");
		}
		if (!m_client.processPacket(m_packetType))
		{
			this->output("Failed to process packet");
		}
		else
		{
			this->output("Processed packet successfully");
		}
	}
}

void app::sys::NetworkSystem::output(std::string const & msg) const
{
	if constexpr (s_DEBUG_MODE)
	{
		app::Console::writeLine(msg);
	}
}

void app::sys::NetworkSystem::output(std::initializer_list<std::string> const & msgs) const
{
	if constexpr (s_DEBUG_MODE)
	{
		app::Console::writeLine(msgs);
	}
}
