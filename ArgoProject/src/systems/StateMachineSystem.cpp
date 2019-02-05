#include "stdafx.h"
#include "StateMachineSystem.h"

// components
#include "components/StateMachine.h"

void app::sys::StateMachineSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::StateMachine>().each([&dt](app::Entity const entity, comp::StateMachine & stateMachine)
	{
		if (stateMachine.instance) { stateMachine.instance->update(dt); }
	});
}
