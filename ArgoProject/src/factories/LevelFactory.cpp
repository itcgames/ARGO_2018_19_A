#include "stdafx.h"
#include "LevelFactory.h"

#include "parameters/DestructibleParameters.h"

#include "factories/WallFactory.h"
#include "factories/HazardFactory.h"
#include "factories/PlatformFactory.h"
#include "factories/AIFactory.h"
#include "factories/entities/EnemyFactory.h"
#include "factories/entities/GoalFactory.h"
#include "factories/DestructibleBlockFactory.h"
#include "factories/FacadeFactory.h"


std::vector<app::Entity> app::fact::LevelFactory::create()
{
	auto entities = std::vector<app::Entity>();
	entities.reserve(50);

	auto position = math::Vector2f(0, 0);
	auto size = math::Vector2f(0, 0);
	
	//enemies
	{
		auto enemyFactory = fact::EnemyFactory(position, size);

		position = math::Vector2f(800, 450);
		size = math::Vector2f(50, 50);
		entities.push_back(enemyFactory.create());

		position = math::Vector2f(1000, 450);
		size = math::Vector2f(50, 50);
		entities.push_back(enemyFactory.create());

		//position = math::Vector2f(630, 200);
		//size = math::Vector2f(50, 50);
		//entities.push_back(enemyFactory.create());
	}

	// walls
	{
		auto wallFactory = fact::WallFactory(position, size);

		position = math::Vector2f(600, 350);
		size = math::Vector2f(50, 250);
		entities.push_back(wallFactory.create());

		position = app::math::Vector2f(875, 500);
		size = app::math::Vector2f(600, 50);
		entities.push_back(wallFactory.create());
		
		position = app::math::Vector2f(1150, 350);
		size = app::math::Vector2f(50, 250);
		entities.push_back(wallFactory.create());
	}
	// destructible blocks
	{
		auto destructibleParams = app::par::DestructibleParameters(position, size);
		auto facade = fact::FacadeFactory(position, size);

		position = app::math::Vector2f(1400, 550);
		size = app::math::Vector2f(200, 50);
		destructibleParams.attachedArea = facade.create();

		auto destructibleFactory = fact::DestructibleBlockFactory(destructibleParams);

		position = app::math::Vector2f(1400, 500);
		size = app::math::Vector2f(50, 50);
		entities.push_back(destructibleFactory.create());
	}
	// hazards
	{
		auto hazardFactory = fact::HazardFactory(position, size);
		
		position = app::math::Vector2f(500, 500);
		size = app::math::Vector2f(50, 50);
		entities.push_back(hazardFactory.create());

		position = app::math::Vector2f(0, 2000);
		size = app::math::Vector2f(40000000, 50);
		entities.push_back(hazardFactory.create());
	}
	// platforms
	{
		auto platformFactory = fact::PlatformFactory(position, size);

		position = app::math::Vector2f(875, 300);
		size = app::math::Vector2f(200, 50);
		entities.push_back(platformFactory.create());

		position = app::math::Vector2f(875, 100);
		size = app::math::Vector2f(200, 50);
		entities.push_back(platformFactory.create());
	}
	// goal
	{
		auto goal = fact::GoalFactory(position, size);

		position = app::math::Vector2f(1300, 500);
		size = app::math::Vector2f(50, 50);
		entities.push_back(goal.create());
	}

	return entities;
}