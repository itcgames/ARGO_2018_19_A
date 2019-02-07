#include "stdafx.h"
#include "BaseCommand.h"
#include "singletons/RegistrySingleton.h"

app::cmnd::BaseCommand::BaseCommand()
	: m_registry(app::sin::Registry::get())
{
}
