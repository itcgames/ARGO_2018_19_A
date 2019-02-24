#include "stdafx.h"
#include "DiscFactory.h"
#include "components/Motion.h"
#include "components/Dimensions.h"
#include "components/Location.h"
#include "components/Input.h"
#include "components/Collision.h"
#include "components/Damage.h"
#include "components/Render.h"
#include "components/Layer.h"
#include "components/Disc.h"

app::fact::DiscFactory::DiscFactory(app::Entity const _entity)
	: m_entity(_entity)
{
}

app::Entity const app::fact::DiscFactory::create()
{
	//entity that is attacking location comp
	auto& location = m_registry.get<comp::Location>(m_entity);
	//entity that is attacking dimensions comp
	auto& dimensions = m_registry.get<comp::Dimensions>(m_entity);
	//entity that is attacking input comp (this helps track which way the character is facing)
	auto& input = m_registry.get<comp::Input>(m_entity);


	app::Entity const entity = EntityFactory::create();


	//dimensions
	auto dimensionsComp = comp::Dimensions();
	dimensionsComp.size = { dimensions.size.x / 2, 100.0f };
	dimensionsComp.origin = { dimensionsComp.size.x / 2, dimensionsComp.size.y / 2 };
	m_registry.assign<decltype(dimensionsComp)>(entity, std::move(dimensionsComp));

	//collision component
	auto collision = comp::Collision();
	collision.bounds = cute::c2AABB();
	m_registry.assign<decltype(collision)>(entity, std::move(collision));

	//disc component
	auto discCmp = comp::Disc();
	discCmp.discImpulse = 1000.0f;
	discCmp.offset = { dimensions.size.x / 2 + dimensionsComp.size.x / 2 + 0.5f, 0.0f };
	m_registry.assign<decltype(discCmp)>(entity, std::move(discCmp));


	//location
	auto locationComp = comp::Location();
	if (input.isRight)
	{
		locationComp.position = location.position + discCmp.offset;
	}
	else
	{
		locationComp.position = location.position - discCmp.offset;
	}
	locationComp.orientation = location.orientation;
	m_registry.assign<decltype(locationComp)>(entity, std::move(locationComp));

	auto damage = comp::Damage();
	damage.damage = 1;
	m_registry.assign<decltype(damage)>(entity, std::move(damage));


	//TODO: remove after debug done or add debug tag
	auto layer = comp::Layer();
	layer.zIndex = 150u;
	m_registry.assign<decltype(layer)>(entity, std::move(layer));

	auto render = comp::Render();
	render.texture = m_resourceManager.getTexture(app::res::TextureKey::DebugColBox);
	m_registry.assign<decltype(render)>(entity, std::move(render));

	auto motionCmp = comp::Motion();
	motionCmp.speed = discCmp.discImpulse;
	motionCmp.direction = 0;
	motionCmp.drag = 1.0f;
	motionCmp.dragCutoff = 0.1f;
	motionCmp.maxSpeed = 1000.0f;
	m_registry.assign<decltype(motionCmp)>(entity, std::move(motionCmp));


	return entity;
}
