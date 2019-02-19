#include "stdafx.h"
#include "FaceLeftCommand.h"
#include "components/Input.h"

app::cmnd::FaceLeftCommand::FaceLeftCommand(app::Entity const _entity)
	: m_entity(_entity)
{
}

void app::cmnd::FaceLeftCommand::execute()
{
	auto& input = m_registry.get<comp::Input>(m_entity);
	input.isRight = false;
}
