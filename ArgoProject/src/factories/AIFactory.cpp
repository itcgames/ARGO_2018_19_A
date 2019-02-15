#include "stdafx.h"
#include "AIFactory.h"

#include "factories/NodeFactory.h"

#include "components/Node.h"

#include "commands/MoveCommand.h"
#include "commands/JumpCommand.h"
#include "commands/DashCommand.h"
#include "commands/FaceLeftCommand.h"
#include "commands/FaceRightCommand.h"
#include "commands/DropCommand.h"

app::fact::AIFactory::AIFactory(math::Vector2f pos, math::Vector2f size)
	: m_position(pos), m_size(size)
{
}

app::Entity const app::fact::AIFactory::create()
{
	app::Entity const entity = EntityFactory::create();


	std::list<std::shared_ptr<cmnd::BaseCommand>> lcmnds;
	std::list<std::shared_ptr<cmnd::BaseCommand>> icmnds;

	lcmnds.push_back(std::make_shared<cmnd::MoveCommand>(entity, 0, 20));
	m_nodes.push_back(app::fact::NodeFactory(math::Vector2f(875, 450), lcmnds, icmnds).create());
	return entity;
}
