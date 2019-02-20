#include "stdafx.h"
#include "ButtonMainMenuMultiplayerCommand.h"
#include "singletons/ClientSingleton.h"

app::cmnd::ButtonMainMenuMultiplayerCommand::ButtonMainMenuMultiplayerCommand()
	: BaseCommand()
	, m_client(app::sin::Client::get())
{
}
