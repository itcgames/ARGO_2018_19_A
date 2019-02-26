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
		auto wallFactory = fact::WallFactory(position, size);
		//1
		position = math::Vector2f(400, -100);
		size = math::Vector2f(800, 4000);
		entities.push_back(wallFactory.create());
		//2
		position = app::math::Vector2f(850, 700);
		size = app::math::Vector2f(600, 1050);
		entities.push_back(wallFactory.create());
		//3
		position = app::math::Vector2f(1200, 575);
		size = app::math::Vector2f(100, 800);
		entities.push_back(wallFactory.create());
		//4
		position = app::math::Vector2f(1300, 675);
		size = app::math::Vector2f(100, 800);
		entities.push_back(wallFactory.create());
		//5
		position = app::math::Vector2f(1400, 775);
		size = app::math::Vector2f(100, 800);
		entities.push_back(wallFactory.create());
		//6
		position = app::math::Vector2f(1650, 875);
		size = app::math::Vector2f(400, 800);
		entities.push_back(wallFactory.create());
		//7
		position = app::math::Vector2f(2050, 675);
		size = app::math::Vector2f(400, 1000);
		entities.push_back(wallFactory.create());
		//8
		position = app::math::Vector2f(2450, 450);
		size = app::math::Vector2f(400, 1000);
		entities.push_back(wallFactory.create());
		//9
		position = app::math::Vector2f(2950, 450);
		size = app::math::Vector2f(600, 2925);
		entities.push_back(wallFactory.create());
		//10
		position = app::math::Vector2f(1950, -565);
		size = app::math::Vector2f(600, 100);
		entities.push_back(wallFactory.create());
		//11
		position = app::math::Vector2f(750, -600);
		size = app::math::Vector2f(600, 100);
		entities.push_back(wallFactory.create());
		//12
		position = app::math::Vector2f(3200, -1400);
		size = app::math::Vector2f(600, 100);
		entities.push_back(wallFactory.create());
		//13
		position = app::math::Vector2f(3650, -900);
		size = app::math::Vector2f(300, 1000);
		entities.push_back(wallFactory.create());
		//14
		position = app::math::Vector2f(3650, 400);
		size = app::math::Vector2f(800, 700);
		entities.push_back(wallFactory.create());

	}
	// destructible blocks
	{
		auto destructibleParams = app::par::DestructibleParameters(position, size);
		auto facade = fact::FacadeFactory(position, size);

		position = app::math::Vector2f(3850, -175);
		size = app::math::Vector2f(400, 450);
		destructibleParams.attachedArea = facade.create();

		auto destructibleFactory = fact::DestructibleBlockFactory(destructibleParams);

		position = app::math::Vector2f(3650, -175);
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
		auto platformFactory = fact::PlatformFactory(position, size);

		//1
		position = app::math::Vector2f(1650, 190);
		size = app::math::Vector2f(400, 30);
		entities.push_back(platformFactory.create());

		//2
		position = app::math::Vector2f(2050, -200);
		size = app::math::Vector2f(400, 30);
		entities.push_back(platformFactory.create());

		//3
		position = app::math::Vector2f(2450, -400);
		size = app::math::Vector2f(400, 30);
		entities.push_back(platformFactory.create());

		//4
		position = app::math::Vector2f(2450, -600);
		size = app::math::Vector2f(400, 30);
		entities.push_back(platformFactory.create());

		//5
		position = app::math::Vector2f(900, -800);
		size = app::math::Vector2f(200, 30);
		entities.push_back(platformFactory.create());

		//6
		position = app::math::Vector2f(900, -1000);
		size = app::math::Vector2f(200, 30);
		entities.push_back(platformFactory.create());

		//7
		position = app::math::Vector2f(1500, -1000);
		size = app::math::Vector2f(200, 30);
		entities.push_back(platformFactory.create());

		//8
		position = app::math::Vector2f(2100, -1000);
		size = app::math::Vector2f(200, 30);
		entities.push_back(platformFactory.create());

		//9
		position = app::math::Vector2f(3375, -1000);
		size = app::math::Vector2f(250, 30);
		entities.push_back(platformFactory.create());


		//position = app::math::Vector2f(875, 300);
		//size = app::math::Vector2f(200, 50);
		//entities.push_back(platformFactory.create());

	}
	// goal
	{
		/*auto goal = fact::GoalFactory(position, size);

		position = app::math::Vector2f(1500, 500);
		size = app::math::Vector2f(50, 50);
		entities.push_back(goal.create());*/
	}

	return entities;
}