#include "stdafx.h"
#include "Game.h"

int main(int argc, char** argv)
{
	using clock = std::chrono::high_resolution_clock;
	constexpr app::time::nanoseconds updateStep =
		app::time::toNanos(std::chrono::duration<double, std::milli>(1 / 60.0 * 1000.0));
	clock::time_point deltaTimePoint = clock::now();
	app::time::nanoseconds elapsedTime = updateStep;
	app::time::nanoseconds deltaRenderStep = app::time::nanoseconds::zero();

	auto game = app::Game();

	while (game.isRunning())
	{
		game.pollEvents();
		deltaRenderStep =
			(elapsedTime += app::time::toNanos(clock::now() - deltaTimePoint));
		deltaTimePoint = clock::now();
		while (elapsedTime > updateStep)
		{
			game.update(app::time::toSeconds(updateStep));
			elapsedTime -= updateStep;
		}
		game.render(app::time::toSeconds(deltaRenderStep));
	}

	return EXIT_SUCCESS;
}