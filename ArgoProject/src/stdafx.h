// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


#ifdef _DEBUG

/*********************************/
/**    BEGIN Debug Libraries    **/
/*********************************/

/*********************************/
/**     END Debug Libraries     **/
/*********************************/

#else

/*********************************/
/**   BEGIN Release Libraries   **/
/*********************************/

/*********************************/
/**    END Release Libraries    **/
/*********************************/

#endif

/*********************************/
/** BEGIN Independant Libraries **/
/*********************************/

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2test.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_net.lib")
#pragma comment(lib, "SDL2_ttf.lib")

/*********************************/
/**  END Independant Libraries  **/
/*********************************/

// STL Common C libraries
#include <cstddef>
#include <cstdint>

// STL Containers
#include <iterator>
#include <array>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <vector>
#include <stack>
#include <queue>

// STL Dynamic Memory Management Libraries
#include <new>
#include <scoped_allocator>
#include <memory>
#include <memory_resource>

// STL Error Libraries
#include <exception>
#include <stdexcept>
#include <system_error>

// STL Utility libraries
#include <type_traits>
#include <random>
#include <chrono>
#include <functional>
#include <tuple>
#include <initializer_list>
#include <limits>
#include <variant>
#include <optional>

// STL Input/Output libraries
#include <string>
#include <sstream>
#include <istream>
#include <ostream>
#include <fstream>
#include <iostream>
#include <filesystem>

// STL Multithreading libraries
#include <thread>
#include <atomic>
#include <mutex>
#include <shared_mutex>
#include <future>
#include <condition_variable>

// SDL2 Library
#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

// SDL2_image Library
#include <SDL/SDL_image.h>

// SDL2_net Library
#include <SDL/SDL_net.h>

// SDL2_ttf Library
#include <SDL/SDL_ttf.h>

// Entt Library
#include <Entt/entt.hpp>

//
// Includes here
//

#include "input/ControllerHandler.h"
#include "input/Keyhandler.h"
#include "input/MouseHandler.h"

#include "math/Math.h"
#include "math/Vector2.h"
#include "math/Rect.h"

#include "utilities/Time.h"
#include "shared/utilities/Console.h"
#include "utilities/makers.h"

namespace app
{
	using Entity = std::uint32_t;
	using Registry = entt::Registry<Entity>;
	namespace inp
	{
		using KeyCode = SDL_Keycode;
		using KeyHandler = Keyhandler<KeyCode>;
		using MouseButtonCode = std::uint8_t;
		using MouseHandler = Mousehandler<MouseButtonCode>;
		using ControllerIndex = std::int32_t;
		using ControllerButtonCode = SDL_GameControllerButton;
		using ControllerAxisCode = SDL_GameControllerAxis;
		using ControllerAxisValue = Sint16;
		using ControllerHandler = Controllerhandler<ControllerIndex, ControllerAxisCode, ControllerAxisValue, ControllerButtonCode>;
	}
}
