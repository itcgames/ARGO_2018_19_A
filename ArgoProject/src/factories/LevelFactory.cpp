#include "stdafx.h"
#include "LevelFactory.h"

#include "factories/WallFactory.h"

app::fact::LevelFactory::LevelFactory() {

}

app::Entity const app::fact::LevelFactory::create() {
	auto entity = fact::WallFactory(app::math::Vector2f(600, 300)).create();
	return entity;
}