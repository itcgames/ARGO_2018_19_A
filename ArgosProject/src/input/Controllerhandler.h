#ifndef _INPUT_CONTROLLER_HANDLER_H
#define _INPUT_CONTROLLER_HANDLER_H

#include "deleters/SdlDeleter.h"

namespace app::inp
{
	template<typename Index, typename Axis, typename Button>
	class Controllerhandler
	{
	private: // Private type definitions
		typedef std::pair<const Button, bool> ButtonPair;
		typedef std::map<const Button, bool> ButtonMap;
		typedef std::map<const Axis, float> AxisMap;
		struct ControllerMaps
		{
			app::del::UPtrGameController controller;
			ButtonMap buttonNowMap;
			ButtonMap buttonPrevMap;
			AxisMap axisMap;
		};
		typedef std::map<Index, ControllerMaps> Controllers;
	public: // Constructors/Destructor/Assignments
		Controllerhandler();
		~Controllerhandler() = default;

		Controllerhandler(Controllerhandler const &) = default;
		Controllerhandler(Controllerhandler &&) = default;

		Controllerhandler & operator=(Controllerhandler const &) = default;
		Controllerhandler & operator=(Controllerhandler &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		void updateButton(Index const & index, Button const & button, bool pressed);
		void update();

		bool isButtonDown(Index const & index, Button const & button) const;
		bool isButtonDown(Index const & index, std::initializer_list<Button> const & buttons) const;
		bool isButtonUp(Index const & index, Button const & button) const;
		bool isButtonUp(Index const & index, std::initializer_list<Button> const & buttons) const;
		bool isButtonPressed(Index const & index, Button const & button) const;
		bool isButtonPressed(Index const & index, std::initializer_list<Button> const & buttons) const;

	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
		static void updateControllers(Controllers & controllers);
		static void updateButton(ButtonMap & map, ButtonMap & prevMap, Button const & button, bool pressed);
		static bool isButtonDown(ButtonMap const & map, Button const & button);
		static bool isButtonDown(ButtonMap const & map, std::initializer_list<Button> const & buttons);
		static bool isButtonUp(ButtonMap const & map, Button const & button);
		static bool isButtonUp(ButtonMap const & map, std::initializer_list<Button> const & buttons);
		static bool isButtonPressed(ButtonMap const & map, ButtonMap const & prevMap, Button const & button);
		static bool isButtonPressed(ButtonMap const & map, ButtonMap const & prevMap, std::initializer_list<Button> const & buttons);
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
		Controllers m_controllers;
	};

	template<typename Index, typename Axis, typename Button>
	Controllerhandler<Index, Axis, Button>::Controllerhandler()
		: m_controllers()
	{
		updateControllers(m_controllers);
	}

	template<typename Index, typename Axis, typename Button>
	void Controllerhandler<Index, Axis, Button>::updateButton(Index const & index, Button const & button, bool pressed)
	{
		if (auto const & controllerItt = m_controllers.find(index); controllerItt != m_controllers.end())
		{
			auto &[i, controller] = *controllerItt;
			Controllerhandler<Index, Axis, Button>::updateButton(controller.buttonNowMap, controller.buttonPrevMap, button, pressed);
		}
	}

	template<typename Index, typename Axis, typename Button>
	void app::inp::Controllerhandler<Index, Axis, Button>::update()
	{
		Controllerhandler<Index, Axis, Button>::updateControllers(m_controllers);
	}

	template<typename Index, typename Axis, typename Button>
	bool Controllerhandler<Index, Axis, Button>::isButtonDown(Index const & index, Button const & button) const
	{
		if (auto const & controllerItt = m_controllers.find(index); controllerItt != m_controllers.end())
		{
			return Controllerhandler<Index, Axis, Button>::isButtonDown(controllerItt->second.buttonNowMap, button);
		}
		return false;
	}

	template<typename Index, typename Axis, typename Button>
	bool Controllerhandler<Index, Axis, Button>::isButtonDown(Index const & index, std::initializer_list<Button> const & buttons) const
	{
		if (auto const & controllerItt = m_controllers.find(index); controllerItt != m_controllers.end())
		{
			return Controllerhandler<Index, Axis, Button>::isButtonDown(controllerItt->second.buttonNowMap, buttons);
		}
		return false;
	}

	template<typename Index, typename Axis, typename Button>
	bool Controllerhandler<Index, Axis, Button>::isButtonUp(Index const & index, Button const & button) const
	{
		if (auto const & controllerItt = m_controllers.find(index); controllerItt != m_controllers.end())
		{
			return Controllerhandler<Index, Axis, Button>::isButtonUp(controllerItt->second.buttonNowMap, button);
		}
		return false;
	}

	template<typename Index, typename Axis, typename Button>
	bool Controllerhandler<Index, Axis, Button>::isButtonUp(Index const & index, std::initializer_list<Button> const & buttons) const
	{
		if (auto const & controllerItt = m_controllers.find(index); controllerItt != m_controllers.end())
		{
			return Controllerhandler<Index, Axis, Button>::isButtonUp(controllerItt->second.buttonNowMap, buttons);
		}
		return false;
	}

	template<typename Index, typename Axis, typename Button>
	bool Controllerhandler<Index, Axis, Button>::isButtonPressed(Index const & index, Button const & button) const
	{
		if (auto const & controllerItt = m_controllers.find(index); controllerItt != m_controllers.end())
		{
			return Controllerhandler<Index, Axis, Button>::isButtonPressed(controllerItt->second.buttonNowMap, controllerItt->second.buttonPrevMap, button);
		}
		return false;
	}

	template<typename Index, typename Axis, typename Button>
	bool Controllerhandler<Index, Axis, Button>::isButtonPressed(Index const & index, std::initializer_list<Button> const & buttons) const
	{
		if (auto const & controllerItt = m_controllers.find(index); controllerItt != m_controllers.end())
		{
			return Controllerhandler<Index, Axis, Button>::isButtonPressed(controllerItt->second.buttonNowMap, controllerItt->second.buttonPrevMap, buttons);
		}
		return false;
	}

	template<typename Index, typename Axis, typename Button>
	inline void Controllerhandler<Index, Axis, Button>::updateControllers(Controllers & controllers)
	{
		int const numJoysticks = SDL_NumJoysticks();
		for (int i = 0; i < numJoysticks; ++i)
		{
			if (!SDL_IsGameController(i)) { continue; }
			SDL_GameController * controller = nullptr;
			controller = SDL_GameControllerOpen(i);
			auto const key = static_cast<std::uint16_t>(i);
			if (controller == nullptr)
			{
				using ControllerPair = std::pair<std::int16_t, ControllerMaps>;
				auto const predicate = [&key](ControllerPair const & p) constexpr { return p.first == key; };
				controllers.erase(std::remove_if(controllers.begin(), controllers.end(), predicate));
				continue;
			}
			if (auto const & itt = controllers.find(key); itt != controllers.end())
			{
				auto &[index, controllerMaps] = *itt;
				controllerMaps.buttonPrevMap.swap(controllerMaps.buttonNowMap);
			}
			else
			{
				auto controllerMaps = ControllerMaps();
				controllerMaps.controller = del::UPtrGameController(controller);
				controllerMaps.buttonNowMap = decltype(controllerMaps.buttonNowMap)();
				controllerMaps.buttonPrevMap = decltype(controllerMaps.buttonPrevMap)();
				controllerMaps.axisMap = decltype(controllerMaps.axisMap)();
				controllers.insert({ static_cast<std::int16_t>(i), std::move(controllerMaps) });
			}
		}
	}

	template<typename Index, typename Axis, typename Button>
	inline void Controllerhandler<Index, Axis, Button>::updateButton(ButtonMap & map, ButtonMap & prevMap, Button const & button, bool pressed)
	{
		if (auto const & itt = map.find(button); itt != map.end())
		{
			auto &[key, value] = *itt;
			value = pressed;
		}
		else
		{
			map.insert({ button, pressed });
			prevMap.insert({ button, !pressed });
		}
	}

	template<typename Index, typename Axis, typename Button>
	inline bool Controllerhandler<Index, Axis, Button>::isButtonDown(ButtonMap const & map, Button const & button)
	{
		const auto predicate = [&button](ButtonPair const & p) constexpr { return p.first == button && p.second; };
		return std::find_if(map.begin(), map.end(), predicate) != map.end();
	}

	template<typename Index, typename Axis, typename Button>
	inline bool Controllerhandler<Index, Axis, Button>::isButtonDown(ButtonMap const & map, std::initializer_list<Button> const & buttons)
	{
		const auto predicate = [&buttons](ButtonPair const & p) constexpr
		{
			return p.second &&
				std::find_if(buttons.begin(), buttons.end(), [&p](Button const & button) constexpr { return p.first == button; }) != buttons.end();
		};
		return std::find_if(map.begin(), map.end(), predicate) != map.end();
	}

	template<typename Index, typename Axis, typename Button>
	inline bool Controllerhandler<Index, Axis, Button>::isButtonUp(ButtonMap const & map, Button const & button)
	{
		const auto predicate = [&button](ButtonPair const & p) constexpr { return p.first == button && !p.second; };
		return std::find_if(map.begin(), map.end(), predicate) != map.end();
	}

	template<typename Index, typename Axis, typename Button>
	inline bool Controllerhandler<Index, Axis, Button>::isButtonUp(ButtonMap const & map, std::initializer_list<Button> const & buttons)
	{
		const auto predicate = [&buttons](ButtonPair const & p) constexpr
		{
			return !p.second &&
				std::find_if(buttons.begin(), buttons.end(), [&p](Button const & button) constexpr { return p.first == button; }) != buttons.end();
		};
		return std::find_if(map.begin(), map.end(), predicate) != map.end();
	}

	template<typename Index, typename Axis, typename Button>
	inline bool Controllerhandler<Index, Axis, Button>::isButtonPressed(ButtonMap const & map, ButtonMap const & prevMap, Button const & button)
	{
		if (auto const & itt = map.find(button); itt != map.end())
		{
			if (auto const & prevItt = prevMap.find(itt->first); prevItt != prevMap.end())
				return itt->second && !prevItt->second;
			else
				return itt->second;
		}
		return false;
	}

	template<typename Index, typename Axis, typename Button>
	inline bool Controllerhandler<Index, Axis, Button>::isButtonPressed(ButtonMap const & map, ButtonMap const & prevMap, std::initializer_list<Button> const & buttons)
	{
		for (auto const &[mapKey, mapValue] : map)
		{
			if (std::find(buttons.begin(), buttons.end(), mapKey) == buttons.end())
				continue;
			if (auto const & result = prevMap.find(mapKey); result != prevMap.end())
				return mapValue && !result->second;
			return mapValue;
		}
		return false;
	}
}

#endif // !_INPUT_CONTROLLER_HANDLER_H
