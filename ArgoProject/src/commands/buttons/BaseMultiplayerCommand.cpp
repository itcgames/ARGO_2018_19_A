#include "stdafx.h"
#include "BaseMultiplayerCommand.h"
#include "singletons/ClientSingleton.h"

app::cmnd::BaseMultiplayerCommand::BaseMultiplayerCommand()
	: BaseCommand()
	, m_client(app::sin::Client::get())
{
}
