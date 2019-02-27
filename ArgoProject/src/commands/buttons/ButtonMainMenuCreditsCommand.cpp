#include "stdafx.h"
#include "ButtonMainMenuCreditsCommand.h"

app::cmnd::ButtonMainMenuCreditsCommand::ButtonMainMenuCreditsCommand(app::sce::SceneType & sceneControl)
	: BaseCommand()
	, m_sceneControl(sceneControl)
{
}

void app::cmnd::ButtonMainMenuCreditsCommand::execute()
{
	m_sceneControl = app::sce::SceneType::Credits;
}
