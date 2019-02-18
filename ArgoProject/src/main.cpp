#include "stdafx.h"
#include "Game.h"

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != NULL)
	{
		app::Console::writeLine({ "ERROR: SDL Failed to initialize [", SDL_GetError(), "]" });
		return EXIT_FAILURE;
	}
	if (SDLNet_Init() != NULL)
	{
		app::Console::writeLine({ "ERROR: SDL_net Failed to initialize [", SDLNet_GetError(), "]" });
		return EXIT_FAILURE;
	}
	if (TTF_Init() != NULL)
	{
		app::Console::writeLine({ "ERROR: SDL_ttf Failed to initialize [", TTF_GetError(), "]" });
		return EXIT_FAILURE;
	}

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