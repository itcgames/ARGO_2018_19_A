#include "stdafx.h"
#include "BaseCommand.h"
#include "singletons/RegistrySingleton.h"

app::cmnd::BaseCommand::BaseCommand()
	: m_registry(app::sin::Registry::get())
{
}

void app::cmnd::BaseCommand::output(std::string const & message) const
{
	if constexpr (s_DEBUG_MODE)
	{
		app::Console::writeLine(message);
	}
}

void app::cmnd::BaseCommand::output(std::initializer_list<std::string> const & messages) const
{
	if constexpr (s_DEBUG_MODE)
	{
		app::Console::writeLine(messages);
	}
}
