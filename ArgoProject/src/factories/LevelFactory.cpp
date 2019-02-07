#include "stdafx.h"
#include "LevelFactory.h"

#include "factories/WallFactory.h"

app::fact::LevelFactory::LevelFactory()
{

}

std::vector<app::Entity> app::fact::LevelFactory::create()
{
	auto entities = std::vector<app::Entity>();
	entities.push_back(fact::WallFactory(app::math::Vector2f(600, 350), app::math::Vector2f(50, 50)).create());
	entities.push_back(fact::WallFactory(app::math::Vector2f(600, 400), app::math::Vector2f(50, 50)).create());
	entities.push_back(fact::WallFactory(app::math::Vector2f(600, 450), app::math::Vector2f(50, 50)).create());
	entities.push_back(fact::WallFactory(app::math::Vector2f(875, 500), app::math::Vector2f(600, 50)).create());
	//entities.push_back(fact::WallFactory(app::math::Vector2f(650, 500), app::math::Vector2f(50, 50)).create());
	//entities.push_back(fact::WallFactory(app::math::Vector2f(700, 500), app::math::Vector2f(50, 50)).create());
	//entities.push_back(fact::WallFactory(app::math::Vector2f(750, 500), app::math::Vector2f(50, 50)).create());
	//entities.push_back(fact::WallFactory(app::math::Vector2f(800, 500), app::math::Vector2f(50, 50)).create());
	//entities.push_back(fact::WallFactory(app::math::Vector2f(850, 500), app::math::Vector2f(50, 50)).create());
	//entities.push_back(fact::WallFactory(app::math::Vector2f(900, 500), app::math::Vector2f(50, 50)).create());
	//entities.push_back(fact::WallFactory(app::math::Vector2f(950, 500), app::math::Vector2f(50, 50)).create());
	//entities.push_back(fact::WallFactory(app::math::Vector2f(1000, 500), app::math::Vector2f(50, 50)).create());
	//entities.push_back(fact::WallFactory(app::math::Vector2f(1050, 500), app::math::Vector2f(50, 50)).create());
	//entities.push_back(fact::WallFactory(app::math::Vector2f(1100, 500), app::math::Vector2f(50, 50)).create());
	//entities.push_back(fact::WallFactory(app::math::Vector2f(1150, 500), app::math::Vector2f(50, 50)).create());
	entities.push_back(fact::WallFactory(app::math::Vector2f(1150, 450), app::math::Vector2f(50, 50)).create());
	entities.push_back(fact::WallFactory(app::math::Vector2f(1150, 400), app::math::Vector2f(50, 50)).create());
	entities.push_back(fact::WallFactory(app::math::Vector2f(1150, 350), app::math::Vector2f(50, 50)).create());

	return entities;
}