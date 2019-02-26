#include "stdafx.h"
#include "TutorialLevelFactory.h"

#include "parameters/DestructibleParameters.h"

#include "factories/WallFactory.h"
#include "factories/HazardFactory.h"
#include "factories/PlatformFactory.h"
#include "factories/AIFactory.h"
#include "factories/entities/EnemyFactory.h"
#include "factories/entities/GoalFactory.h"
#include "factories/DestructibleBlockFactory.h"
#include "factories/FacadeFactory.h"


std::vector<app::Entity> app::fact::TutorialLevelFactory::create()
{
	auto entities = std::vector<app::Entity>();
	entities.reserve(50);

	auto position = math::Vector2f(0, 0);
	auto size = math::Vector2f(0, 0);
	auto tiles = math::Vector2i(0, 0);
	std::uint32_t platformWidth;

	// walls
	{ 
		size = math::Vector2f(50, 50);

		auto wallFactory = fact::WallFactory(position, size, tiles);
		auto wallEntities = std::vector<app::Entity>();

		//1
		position = math::Vector2f(400, -100);
		//size = math::Vector2f(800, 4000);
		tiles = math::Vector2i(16, 80);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, std::make_move_iterator(wallEntities.begin())
			, std::make_move_iterator(wallEntities.end()));
		//2
		position = app::math::Vector2f(850, 700);
		tiles = math::Vector2i(12, 21);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, std::make_move_iterator(wallEntities.begin())
			, std::make_move_iterator(wallEntities.end()));
		//3
		position = app::math::Vector2f(1200, 575);
		tiles = math::Vector2i(2, 16);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, std::make_move_iterator(wallEntities.begin())
			, std::make_move_iterator(wallEntities.end()));
		//4
		position = app::math::Vector2f(1300, 675);
		tiles = math::Vector2i(2, 16);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, std::make_move_iterator(wallEntities.begin())
			, std::make_move_iterator(wallEntities.end()));
		//5
		position = app::math::Vector2f(1400, 775);
		tiles = math::Vector2i(2, 16);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, std::make_move_iterator(wallEntities.begin())
			, std::make_move_iterator(wallEntities.end()));
		//6
		position = app::math::Vector2f(1650, 875);
		tiles = math::Vector2i(8, 16);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, std::make_move_iterator(wallEntities.begin())
			, std::make_move_iterator(wallEntities.end()));
		//7
		position = app::math::Vector2f(2050, 675);
		tiles = math::Vector2i(8, 20);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, std::make_move_iterator(wallEntities.begin())
			, std::make_move_iterator(wallEntities.end()));
		//8
		position = app::math::Vector2f(2450, 450);
		tiles = math::Vector2i(8, 20);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, std::make_move_iterator(wallEntities.begin())
			, std::make_move_iterator(wallEntities.end()));
		//9
		position = app::math::Vector2f(2950, 450);
		tiles = math::Vector2i(12, 58);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, std::make_move_iterator(wallEntities.begin())
			, std::make_move_iterator(wallEntities.end()));
		//10
		position = app::math::Vector2f(1950, -565);
		tiles = math::Vector2i(12, 2);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, std::make_move_iterator(wallEntities.begin())
			, std::make_move_iterator(wallEntities.end()));
		//11
		position = app::math::Vector2f(750, -600);
		tiles = math::Vector2i(12, 2);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, std::make_move_iterator(wallEntities.begin())
			, std::make_move_iterator(wallEntities.end()));
		//12
		position = app::math::Vector2f(3200, -1400);
		tiles = math::Vector2i(12, 2);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, std::make_move_iterator(wallEntities.begin())
			, std::make_move_iterator(wallEntities.end()));
		//13
		position = app::math::Vector2f(3650, -900);
		tiles = math::Vector2i(6, 20);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, std::make_move_iterator(wallEntities.begin())
			, std::make_move_iterator(wallEntities.end()));
		//14
		position = app::math::Vector2f(3650, 400);
		tiles = math::Vector2i(16, 14);
		wallEntities = wallFactory.create();
		entities.insert(entities.end()
			, std::make_move_iterator(wallEntities.begin())
			, std::make_move_iterator(wallEntities.end()));

	}
	// destructible blocks
	{

		math::Vector2f tileSize = math::Vector2f(50, 50);
		math::Vector2i noTiles = math::Vector2i(1, 4);

		auto destructibleParams = app::par::DestructibleParameters(position, size, tileSize, noTiles);
		auto facade = fact::FacadeFactory(position, tileSize, noTiles);

		position = app::math::Vector2f(3850, -175);
		size = app::math::Vector2f(400, 450);
		noTiles = math::Vector2i(8, 9);
		destructibleParams.attachedArea = facade.create();

		noTiles = math::Vector2i(1, 9);
		auto destructibleFactory = fact::DestructibleBlockFactory(destructibleParams);

		position = app::math::Vector2f(3625, -175);
		size = app::math::Vector2f(50, 450);
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

		auto platformFactory = fact::PlatformFactory(position, size, platformWidth);

		//1
		position = app::math::Vector2f(1650, 190);
		size = app::math::Vector2f(50, 30);
		platformWidth = 8;
		entities.push_back(platformFactory.create());

		//2
		position = app::math::Vector2f(2050, -200);
		size = app::math::Vector2f(50, 30);
		platformWidth = 8;
		entities.push_back(platformFactory.create());

		//3
		position = app::math::Vector2f(2450, -400);
		size = app::math::Vector2f(50, 30);
		platformWidth = 8;
		entities.push_back(platformFactory.create());

		//4
		position = app::math::Vector2f(2450, -600);
		size = app::math::Vector2f(50, 30);
		platformWidth = 8;
		entities.push_back(platformFactory.create());

		//5
		position = app::math::Vector2f(900, -800);
		size = app::math::Vector2f(50, 30);
		platformWidth = 4;
		entities.push_back(platformFactory.create());

		//6
		position = app::math::Vector2f(900, -1000);
		size = app::math::Vector2f(50, 30);
		platformWidth = 4;
		entities.push_back(platformFactory.create());

		//7
		position = app::math::Vector2f(1500, -1000);
		size = app::math::Vector2f(50, 30);
		platformWidth = 4;
		entities.push_back(platformFactory.create());

		//8
		position = app::math::Vector2f(2100, -1000);
		size = app::math::Vector2f(50, 30);
		platformWidth = 4;
		entities.push_back(platformFactory.create());

		//9
		position = app::math::Vector2f(3375, -990);
		size = app::math::Vector2f(50, 30);
		platformWidth = 5;
		entities.push_back(platformFactory.create());


		//position = app::math::Vector2f(875, 300);
		//size = app::math::Vector2f(200, 50);
		//entities.push_back(platformFactory.create());

	}
	// goal
	{
		auto goal = fact::GoalFactory(position, size);

		position = app::math::Vector2f(3850, 0);
		size = app::math::Vector2f(50, 50);
		entities.push_back(goal.create());
	}

	return entities;
}