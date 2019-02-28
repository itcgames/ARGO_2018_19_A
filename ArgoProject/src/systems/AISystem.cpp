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
		if (ai.currentNode.has_value() && nodeView.contains(ai.currentNode.value()))
		{
			auto & currentNode = nodeView.get(ai.currentNode.value());
			if (currentNode.loopCommands.size() > 0)
			{
				if (currentNode.timeCommandsLooped <= currentNode.timeToLoopCommands)
				{
					currentNode.loopCommands.front()->execute();
				}
				currentNode.timeCommandsLooped += dt.count();

			}
			if (ai.initialCommands.size() > 0)
			{
				ai.initialCommands.front()->execute();
				ai.initialCommands.pop_front();
			}
		}
	});
}