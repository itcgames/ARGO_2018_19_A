#include "stdafx.h"
#include "NodeFactory.h"

#include "components/Location.h"
#include "components/Dimensions.h"
#include "components/Render.h"
#include "components/Node.h"
#include "components/Collision.h"

app::fact::NodeFactory::NodeFactory(math::Vector2f const & pos, std::list<std::shared_ptr<app::cmnd::BaseCommand>> const & lcmnds, std::list<std::shared_ptr<app::cmnd::BaseCommand>> const & icmnds)
	: m_position(pos), m_loopCommands(lcmnds), m_initialCommands(icmnds)
{
}

app::Entity const app::fact::NodeFactory::create()
{
	app::Entity const entity = m_registry.create();

	auto location = comp::Location();
	location.position = m_position;
	location.orientation = 0.0f;
	m_registry.assign<decltype(location)>(entity, std::move(location));

	auto dimensions = comp::Dimensions();
	dimensions.size = math::Vector2f(s_RADIUS,s_RADIUS);
	dimensions.origin = dimensions.size / 2.0f;
	m_registry.assign<decltype(dimensions)>(entity, std::move(dimensions));

	auto collision = comp::Collision();
	collision.bounds = cute::c2Circle();
	m_registry.assign<decltype(collision)>(entity, std::move(collision));

	auto render = comp::Render();
	render.texture = m_resourceManager.getTexture(app::res::TextureKey::Debug);
	m_registry.assign<decltype(render)>(entity, std::move(render));

	auto node = comp::Node();
	node.loopCommands = m_loopCommands;
	node.initialCommands = m_initialCommands;
	m_registry.assign<decltype(node)>(entity, std::move(node));

	return entity;
}
