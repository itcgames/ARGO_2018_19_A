#include "stdafx.h"
#include "AISystem.h"

#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/AI.h"
#include "components/Node.h"
#include "commands/MoveCommand.h"
#include "commands/JumpCommand.h"

void app::sys::AISystem::update(app::time::seconds const & dt)
{
	auto nodeView = m_registry.view<comp::Node>();
	m_registry.view<comp::Location, comp::Dimensions, comp::AI>()
		.each([&, this](app::Entity entity, comp::Location & location, comp::Dimensions & dimensions, comp::AI & ai)
	{
		if (ai.m_currentNode.has_value())
		{
			auto & currentNode = nodeView.get(ai.m_currentNode.value());
			currentNode.m_loopCommands.front()->execute();

			if (currentNode.m_initialCommands.size() > 0)
			{
				currentNode.m_initialCommands.front()->execute();
				currentNode.m_initialCommands.pop_front();
			}
		}
	});
}