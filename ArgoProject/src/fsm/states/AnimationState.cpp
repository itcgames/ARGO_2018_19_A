#include "stdafx.h"
#include "AnimationState.h"
#include "singletons/ResourceManagerSingleton.h"
#include "components/StateMachine.h"

app::fsm::sta::AnimationState::AnimationState(app::Entity const entity)
	: EntityState(entity)
	, m_render()
	, m_resourceManager(app::sin::ResourceManager::get())
{
}

void app::fsm::sta::AnimationState::update(app::time::seconds const & dt)
{
	// Retrieve the current state machine for `m_entity`
	// allows you to change the current state of the fsm
	//auto stateMachineView = m_registry.view<comp::StateMachine>();
	//if (stateMachineView.contains(m_entity))
	//{
	//	auto & stateMachine = stateMachineView.get(m_entity);
	//	stateMachine.instance->setState(nullptr);
	//}
}

void app::fsm::sta::AnimationState::start()
{
	auto renderView = m_registry.view<comp::Render, comp::Animator>();

	assert(m_registry.valid(m_entity) && renderView.contains(m_entity));
	m_registry.accommodate<comp::Render>(m_entity, m_render);
	m_registry.accommodate<comp::Animator>(m_entity, m_animator);
}

void app::fsm::sta::AnimationState::end()
{
}
