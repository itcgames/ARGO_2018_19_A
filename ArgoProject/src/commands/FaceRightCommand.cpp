#include "stdafx.h"
#include "FaceRightCommand.h"
#include "components/Input.h"

app::cmnd::FaceRightCommand::FaceRightCommand(app::Entity const _entity)
	: m_entity(_entity)
{
}

void app::cmnd::FaceRightCommand::execute()
{
	auto& input = m_registry.get<comp::Input>(m_entity);
	input.m_isRight = true;
}
