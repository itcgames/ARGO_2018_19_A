#include "stdafx.h"
#include "ButtonMainMenuSinglePlayerCommand.h"

app::cmnd::ButtonMainMenuSinglePlayerCommand::ButtonMainMenuSinglePlayerCommand(app::sce::SceneType & sceneControl)
	: BaseCommand()
	, m_sceneControl(sceneControl)
{
}

void app::cmnd::ButtonMainMenuSinglePlayerCommand::execute()
{
	m_sceneControl = app::sce::SceneType::CharacterSelect;
}
