#include "stdafx.h"
#include "BaseCommand.h"
#include "Registry.h"

app::cmnd::BaseCommand::BaseCommand()
	: m_registry(app::Reg::get())
{
}
