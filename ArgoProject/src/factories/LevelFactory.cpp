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
	std::uint32_t entityWidth;
	
	//enemies
	{
		auto enemyFactory = fact::EnemyFactory(position, size);

		position = math::Vector2f(800, 450);
		size = math::Vector2f(50, 50);
		entities.push_back(enemyFactory.create());

		position = math::Vector2f(1000, 450);
		size = math::Vector2f(50, 50);
		entities.push_back(enemyFactory.create());

		//position = math::Vector2f(1800, 500);
		//size = math::Vector2f(50, 50);
		//entities.push_back(enemyFactory.create());

		//position = math::Vector2f(2920, 950);
		//size = math::Vector2f(50, 50);
		//entities.push_back(enemyFactory.create());

		//position = math::Vector2f(4125, 275);
		//size = math::Vector2f(50, 50);
		//entities.push_back(enemyFactory.create());
	}

	// walls
	{
		auto wallFactory = fact::WallFactory(position, size, numberOfTiles);
		auto wallEntities = std::vector<app::Entity>();
		size = math::Vector2f(50, 50);

		position = math::Vector2f(600, -25);
		numberOfTiles = math::Vector2i(1, 20);
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
		
		position = app::math::Vector2f(2150, 625);
		numberOfTiles = math::Vector2i(1, 14);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, wallEntities.begin()
			, wallEntities.end());

		position = app::math::Vector2f(2400, 300);
		numberOfTiles = math::Vector2i(9, 1);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, wallEntities.begin()
			, wallEntities.end());

		position = app::math::Vector2f(2475, 100);
		numberOfTiles = math::Vector2i(6, 1);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, wallEntities.begin()
			, wallEntities.end());

		position = app::math::Vector2f(2625, 150);
		numberOfTiles = math::Vector2i(1, 7);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, wallEntities.begin()
			, wallEntities.end());

		position = app::math::Vector2f(2750, 0);
		numberOfTiles = math::Vector2i(4, 1);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, wallEntities.begin()
			, wallEntities.end());

		position = app::math::Vector2f(2975, 25);
		numberOfTiles = math::Vector2i(1, 30);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, wallEntities.begin()
			, wallEntities.end());

		position = app::math::Vector2f(2750, 725);
		numberOfTiles = math::Vector2i(8, 2);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, wallEntities.begin()
			, wallEntities.end());

		position = app::math::Vector2f(2900, 350);
		numberOfTiles = math::Vector2i(2, 1);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, wallEntities.begin()
			, wallEntities.end());

		position = app::math::Vector2f(3450, 1000);
		numberOfTiles = math::Vector2i(30, 1);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, wallEntities.begin()
			, wallEntities.end());

		position = app::math::Vector2f(2900, 925);
		numberOfTiles = math::Vector2i(1, 2);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, wallEntities.begin()
			, wallEntities.end());

		position = app::math::Vector2f(4225, 275);
		numberOfTiles = math::Vector2i(1, 30);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, wallEntities.begin()
			, wallEntities.end());

		position = app::math::Vector2f(3550, 500);
		numberOfTiles = math::Vector2i(4, 1);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, wallEntities.begin()
			, wallEntities.end());

		position = app::math::Vector2f(4125, 325);
		numberOfTiles = math::Vector2i(4, 1);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, wallEntities.begin()
			, wallEntities.end());

		position = app::math::Vector2f(3500, 100);
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
		auto facadeFactory = fact::FacadeFactory(position, tileSize, noTiles);

		position = app::math::Vector2f(2525, 225);
		size = app::math::Vector2f(200, 500);
		noTiles = math::Vector2f(4, 4);
		auto facadeEntities = facadeFactory.create();
		destructibleParams.attachedArea = facadeEntities.back();
		entities.insert(entities.end()
			, facadeEntities.begin()
			, facadeEntities.end());

		noTiles = math::Vector2i(1, 4);
		auto destructibleFactory = fact::DestructibleBlockFactory(destructibleParams);

		position = app::math::Vector2f(2400, 175);
		size = app::math::Vector2f(50, 200);
		auto destructibleEntities = destructibleFactory.create();
		entities.insert(entities.end()
			, destructibleEntities.begin()
			, destructibleEntities.end());
	}
	// hazards
	{
		auto hazardFactory = fact::HazardFactory(position, size, entityWidth);
		auto hazardEntities = std::vector<app::Entity>();
		
		position = app::math::Vector2f(1400, 500);
		size = app::math::Vector2f(50, 50);
		entityWidth = 1;
		hazardEntities = hazardFactory.create();
		entities.insert(entities.end()
			, hazardEntities.begin()
			, hazardEntities.end());

		position = app::math::Vector2f(2000, 1500);
		entityWidth = 200;
		hazardEntities = hazardFactory.create();
		entities.insert(entities.end()
			, hazardEntities.begin()
			, hazardEntities.end());

		position = app::math::Vector2f(2900, 300);
		entityWidth = 2;
		hazardEntities = hazardFactory.create();
		entities.insert(entities.end()
			, hazardEntities.begin()
			, hazardEntities.end());
	}
	// platforms
	{
		auto platformFactory = fact::PlatformFactory(position, size, entityWidth);

		position = app::math::Vector2f(875, 300);
		size = app::math::Vector2f(50, 30);
		entityWidth = 5;
		entities.push_back(platformFactory.create());

		position = app::math::Vector2f(875, 100);
		entityWidth = 3;
		entities.push_back(platformFactory.create());

		position = app::math::Vector2f(1800, 300);
		entityWidth = 6;
		entities.push_back(platformFactory.create());

		position = app::math::Vector2f(2900, -10);
		entityWidth = 2;
		entities.push_back(platformFactory.create());

		position = app::math::Vector2f(4075, 775);
		entityWidth = 4;
		entities.push_back(platformFactory.create());

		position = app::math::Vector2f(3050, 675);
		entityWidth = 2;
		entities.push_back(platformFactory.create());
	}
	// goal
	{
		auto goal = fact::GoalFactory(position, size);

		position = app::math::Vector2f(3500, 50);
		size = app::math::Vector2f(50, 50);
		entities.push_back(goal.create());
	}

	return entities;
}