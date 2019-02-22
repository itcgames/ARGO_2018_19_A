#include "stdafx.h"
#include "TestCommand.h"

void app::cmnd::TestCommand::execute()
{
	app::Console::writeLine("Test Command Executed!");
}
