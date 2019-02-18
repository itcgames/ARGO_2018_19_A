#include "stdafx.h"
#include "ButtonMultiplayerCommand.h"
#include "singletons/ClientSingleton.h"

app::cmnd::ButtonMultiplayerCommand::ButtonMultiplayerCommand()
	: BaseCommand()
	, m_client(app::sin::Client::get())
{
}
