#include "stdafx.h"
#include "ButtonMultiplayerCancelCommand.h"
#include "components/Destroy.h"

app::cmnd::ButtonMultiplayerCancelCommand::ButtonMultiplayerCancelCommand(std::vector<app::Entity> const & entities)
	: ButtonMultiplayerCommand()
	, m_entities(entities.cbegin(), entities.cend())
{
}

void app::cmnd::ButtonMultiplayerCancelCommand::setEntites(std::vector<app::Entity> const & entities)
{
	m_entities.reserve(m_entities.size() + entities.size());
	m_entities.insert(m_entities.end(), entities.cbegin(), entities.cend());
}

void app::cmnd::ButtonMultiplayerCancelCommand::execute()
{
	if (!m_client.hasInit()) { return; }
	if (m_client.deinitNetwork())
	{
		this->output("Disconnection from server successful !");
		for (auto entity : m_entities)
		{
			assert(m_registry.valid(entity));
			m_registry.assign<comp::Destroy>(entity);
		}
	}
	else
	{
		this->output("Disconnection from server failed !");
	}
}

void app::cmnd::ButtonMultiplayerCancelCommand::output(std::string const & message) const
{
	if constexpr (s_DEBUG_MODE)
	{
		app::Console::writeLine(message);
	}
}
