#include "stdafx.h"
#include "BaseStateMachine.h"

app::fsm::BaseStateMachine::BaseStateMachine(std::shared_ptr<BaseState> state)
{
}

void app::fsm::BaseStateMachine::setState(std::shared_ptr<BaseState> newState)
{
	m_state = newState;
}
