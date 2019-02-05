#include "stdafx.h"
#include "AnimationState.h"

app::fsm::sta::AnimationState::AnimationState(app::Entity const entity, comp::Render render)
	: EntityState(entity)
	, m_render(std::move(render))
{
}

void app::fsm::sta::AnimationState::update(app::time::seconds const & dt)
{
}

void app::fsm::sta::AnimationState::start()
{
	assert(m_registry.valid(m_entity) && m_registry.has<comp::Render>());
	m_registry.replace<comp::Render>(m_entity, m_render);
}

void app::fsm::sta::AnimationState::end()
{
}
