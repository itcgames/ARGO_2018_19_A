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
	auto numberOfTiles = math::Vector2i{ };
	
	//enemies
	{
		auto enemyFactory = fact::EnemyFactory(position, size);

		position = math::Vector2f(800, 450);
		size = math::Vector2f(50, 50);
		entities.push_back(enemyFactory.create());

		position = math::Vector2f(1000, 450);
		size = math::Vector2f(50, 50);
		entities.push_back(enemyFactory.create());
	}

	// walls
	{
		auto wallFactory = fact::WallFactory(position, size, numberOfTiles);
		auto wallEntities = std::vector<app::Entity>();
		size = math::Vector2f(50, 50);

		position = math::Vector2f(600, 350);
		numberOfTiles = math::Vector2i(1, 5);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, wallEntities.begin()
			, wallEntities.end());

		position = app::math::Vector2f(875, 500);
		numberOfTiles = math::Vector2i(12, 1);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, wallEntities.begin()
			, wallEntities.end());

		position = app::math::Vector2f(1775, 550);
		numberOfTiles = math::Vector2i(16, 1);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, wallEntities.begin()
			, wallEntities.end());
		
		position = app::math::Vector2f(2150, 400);
		numberOfTiles = math::Vector2i(1, 5);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, wallEntities.begin()
			, wallEntities.end());

		position = app::math::Vector2f(2300, 300);
		numberOfTiles = math::Vector2i(5, 1);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, wallEntities.begin()
			, wallEntities.end());
	}
	// destructible blocks
	{
		math::Vector2f tileSize = math::Vector2f(50, 50);
		math::Vector2i noTiles = math::Vector2i(1, 4);
		auto destructibleParams = app::par::DestructibleParameters(position, size, tileSize, noTiles);
		auto facade = fact::FacadeFactory(position, tileSize, noTiles);

		position = app::math::Vector2f(2525, 250);
		size = app::math::Vector2f(200, 600);
		noTiles = math::Vector2f(4, 12);
		destructibleParams.attachedArea = facade.create();

		noTiles = math::Vector2i(1, 4);
		auto destructibleFactory = fact::DestructibleBlockFactory(destructibleParams);

		position = app::math::Vector2f(2400, 175);
		size = app::math::Vector2f(50, 200);
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

		position = app::math::Vector2f(1800, 350);
		size = app::math::Vector2f(200, 50);
		entities.push_back(platformFactory.create());
	}
	// goal
	{
		auto goal = fact::GoalFactory(position, size);

		position = app::math::Vector2f(2500, 550);
		size = app::math::Vector2f(50, 50);
		entities.push_back(goal.create());
	}

	return entities;
}