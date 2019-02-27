#include "stdafx.h"
#include "ButtonMainMenuExitCommand.h"

app::cmnd::ButtonMainMenuExitCommand::ButtonMainMenuExitCommand(app::sce::SceneType & sceneControl)
	: BaseCommand()
	, m_sceneControl(sceneControl)
{
}

void app::cmnd::ButtonMainMenuExitCommand::execute()
{
	m_sceneControl = app::sce::SceneType::Exit;
}
