#ifndef _INPUT_CONTROLLER_HANDLER_H
#define _INPUT_CONTROLLER_HANDLER_H

#include "deleters/SdlDeleter.h"

namespace app::inp
{
	template<typename Index, typename Axis, typename AxisValue, typename Button>
	class Controllerhandler
	{
	private: // Private type definitions
		typedef std::pair<const Button, bool> ButtonPair;
		typedef std::map<const Button, bool> ButtonMap;
		typedef std::map<const Axis, double> AxisMap;
		struct Controller
		{
			app::del::UPtrGameController controller;
			ButtonMap buttonNowMap;
			ButtonMap buttonPrevMap;
			AxisMap axisMap;
		};
		typedef std::map<Index, Controller> Controllers;
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
		void updateAxis(Index const & index, Axis const & axis, AxisValue const & amount);
		void update();

		bool isButtonDown(Index const & index, Button const & button) const;
		bool isButtonDown(Index const & index, std::initializer_list<Button> const & buttons) const;
		bool isButtonUp(Index const & index, Button const & button) const;
		bool isButtonUp(Index const & index, std::initializer_list<Button> const & buttons) const;
		bool isAxisOver(Index const & index, Button const & button) const;
		bool isAxisOver(Index const & index, std::initializer_list<Button> const & buttons) const;
		bool isButtonUnpressed(Index const & index, Button const & button) const;
		bool isButtonUnpressed(Index const & index, std::initializer_list<Button> const & buttons) const;
		double getAxis(Index const & index, Axis const & axis) const;
		std::size_t getNumControllers() const;

		void addController(Index const & index);
		void removeController(Index const & index);

	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
		static void updateControllers(Controllers & controllers);
		static void updateButton(ButtonMap & map, ButtonMap & prevMap, Button const & button, bool pressed);
		static void updateAxis(Controller & controller, Axis const & axis, AxisValue const & value);
		static bool isButtonDown(ButtonMap const & map, Button const & button);
		static bool isButtonDown(ButtonMap const & map, std::initializer_list<Button> const & buttons);
		static bool isButtonUp(ButtonMap const & map, Button const & button);
		static bool isButtonUp(ButtonMap const & map, std::initializer_list<Button> const & buttons);
		static bool isAxisOver(ButtonMap const & map, ButtonMap const & prevMap, Button const & button);
		static bool isAxisOver(ButtonMap const & map, ButtonMap const & prevMap, std::initializer_list<Button> const & buttons);
		static bool isButtonUnpressed(ButtonMap const & map, ButtonMap const & prevMap, Button const & button);
		static bool isButtonUnpressed(ButtonMap const & map, ButtonMap const & prevMap, std::initializer_list<Button> const & buttons);
		static double getAxis(AxisMap const & map, Axis const & axis);
	private: // Private Member Functions
	private: // Private Static Variables
		constexpr static bool DEBUG_CLASS = false;
	private: // Private Member Variables
		Controllers m_controllers;
	};

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	Controllerhandler<Index, Axis, AxisValue, Button>::Controllerhandler()
		: m_controllers()
	{
		updateControllers(m_controllers);
	}

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	void Controllerhandler<Index, Axis, AxisValue, Button>::updateButton(Index const & index, Button const & button, bool pressed)
	{
		if (auto const & controllerItt = m_controllers.find(index); controllerItt != m_controllers.end())
		{
			auto & controller = std::get<Controller>(*controllerItt);
			if constexpr (DEBUG_CLASS)
			{
				Console::write({ "ControllerHandler[", std::to_string(index), "]: " });
			}
			Controllerhandler<Index, Axis, AxisValue, Button>::updateButton(controller.buttonNowMap, controller.buttonPrevMap, button, pressed);
		}
	}

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	void Controllerhandler<Index, Axis, AxisValue, Button>::updateAxis(Index const & index, Axis const & axis, AxisValue const & amount)
	{
		if (auto const & controllerItt = m_controllers.find(index); controllerItt != m_controllers.end())
		{
			auto & controller = std::get<Controller>(*controllerItt);
			if constexpr (DEBUG_CLASS)
			{
				Console::write({ "ControllerHandler[", std::to_string(index), "]: " });
			}
			Controllerhandler<Index, Axis, AxisValue, Button>::updateAxis(controller, axis, amount);
		}
	}

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	void app::inp::Controllerhandler<Index, Axis, AxisValue, Button>::update()
	{
		Controllerhandler<Index, Axis, AxisValue, Button>::updateControllers(m_controllers);
	}

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	bool Controllerhandler<Index, Axis, AxisValue, Button>::isButtonDown(Index const & index, Button const & button) const
	{
		if (auto const & controllerItt = m_controllers.find(index); controllerItt != m_controllers.end())
		{
			auto const & controller = std::get<Controller>(*controllerItt);
			return Controllerhandler<Index, Axis, AxisValue, Button>::isButtonDown(controller.buttonNowMap, button);
		}
		return false;
	}

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	bool Controllerhandler<Index, Axis, AxisValue, Button>::isButtonDown(Index const & index, std::initializer_list<Button> const & buttons) const
	{
		if (auto const & controllerItt = m_controllers.find(index); controllerItt != m_controllers.end())
		{
			auto const & controller = std::get<Controller>(*controllerItt);
			return Controllerhandler<Index, Axis, AxisValue, Button>::isButtonDown(controller.buttonNowMap, buttons);
		}
		return false;
	}

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	bool Controllerhandler<Index, Axis, AxisValue, Button>::isButtonUp(Index const & index, Button const & button) const
	{
		if (auto const & controllerItt = m_controllers.find(index); controllerItt != m_controllers.end())
		{
			auto const & controller = std::get<Controller>(*controllerItt);
			return Controllerhandler<Index, Axis, AxisValue, Button>::isButtonUp(controller.buttonNowMap, button);
		}
		return false;
	}

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	bool Controllerhandler<Index, Axis, AxisValue, Button>::isButtonUp(Index const & index, std::initializer_list<Button> const & buttons) const
	{
		if (auto const & controllerItt = m_controllers.find(index); controllerItt != m_controllers.end())
		{
			auto const & controller = std::get<Controller>(*controllerItt);
			return Controllerhandler<Index, Axis, AxisValue, Button>::isButtonUp(controller.buttonNowMap, buttons);
		}
		return false;
	}

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	bool Controllerhandler<Index, Axis, AxisValue, Button>::isAxisOver(Index const & index, Button const & button) const
	{
		if (auto const & controllerItt = m_controllers.find(index); controllerItt != m_controllers.end())
		{
			auto const & controller = std::get<Controller>(*controllerItt);
			return Controllerhandler<Index, Axis, AxisValue, Button>::isAxisOver(controller.buttonNowMap, controller.buttonPrevMap, button);
		}
		return false;
	}

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	bool Controllerhandler<Index, Axis, AxisValue, Button>::isAxisOver(Index const & index, std::initializer_list<Button> const & buttons) const
	{
		if (auto const & controllerItt = m_controllers.find(index); controllerItt != m_controllers.end())
		{
			auto const & controller = std::get<Controller>(*controllerItt);
			return Controllerhandler<Index, Axis, AxisValue, Button>::isAxisOver(controller.buttonNowMap, controller.buttonPrevMap, buttons);
		}
		return false;
	}

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	bool Controllerhandler<Index, Axis, AxisValue, Button>::isButtonUnpressed(Index const & index, Button const & button) const
	{
		if (auto const & controllerItt = m_controllers.find(index); controllerItt != m_controllers.end())
		{
			auto const & controller = std::get<Controller>(*controllerItt);
			return Controllerhandler<Index, Axis, AxisValue, Button>::isButtonUnpressed(controller.buttonNowMap, controller.buttonPrevMap, button);
		}
		return false;
	}

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	bool Controllerhandler<Index, Axis, AxisValue, Button>::isButtonUnpressed(Index const & index, std::initializer_list<Button> const & buttons) const
	{
		if (auto const & controllerItt = m_controllers.find(index); controllerItt != m_controllers.end())
		{
			auto const & controller = std::get<Controller>(*controllerItt);
			return Controllerhandler<Index, Axis, AxisValue, Button>::isButtonUnpressed(controller.buttonNowMap, controller.buttonPrevMap, buttons);
		}
		return false;
	}

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	double Controllerhandler<Index, Axis, AxisValue, Button>::getAxis(Index const & index, Axis const & axis) const
	{
		if (auto const & controllerItt = m_controllers.find(index); controllerItt != m_controllers.end())
		{
			auto const & controller = std::get<Controller>(*controllerItt);
			return Controllerhandler<Index, Axis, AxisValue, Button>::getAxis(controller.axisMap, axis);
		}
		return 0.0;
	}

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	std::size_t Controllerhandler<Index, Axis, AxisValue, Button>::getNumControllers() const
	{
		return m_controllers.size();
	}

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	void Controllerhandler<Index, Axis, AxisValue, Button>::addController(Index const & index)
	{
		if (!SDL_IsGameController(index)) { Console::writeLine("ERROR: Tried add a joystick to the controller only handler."); return; }
		if (SDL_GameController * pController = SDL_GameControllerOpen(index); pController != nullptr)
		{
			if (auto const & itt = m_controllers.find(index); itt == m_controllers.end())
			{
				auto controller = Controller();
				controller.controller = del::UPtrGameController(pController);
				controller.buttonNowMap = decltype(controller.buttonNowMap)();
				controller.buttonPrevMap = decltype(controller.buttonPrevMap)();
				controller.axisMap = decltype(controller.axisMap)();
				m_controllers.insert({ index, std::move(controller) });
				if constexpr (DEBUG_CLASS)
				{
					Console::writeLine({ "ControllerHandler: Controller[id=", std::to_string(index), "] added" });
				}
			}
		}
	}

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	void Controllerhandler<Index, Axis, AxisValue, Button>::removeController(Index const & index)
	{
		m_controllers.erase(index);
		if constexpr (DEBUG_CLASS)
		{
			Console::writeLine({ "ControllerHandler: Controller[id=", std::to_string(index), "] removed" });
		}
	}

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	inline void Controllerhandler<Index, Axis, AxisValue, Button>::updateControllers(Controllers & controllers)
	{
		for (auto &[index, controller] : controllers)
		{
			controller.buttonPrevMap = controller.buttonNowMap;
		}
	}

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	inline void Controllerhandler<Index, Axis, AxisValue, Button>::updateButton(ButtonMap & map, ButtonMap & prevMap, Button const & button, bool pressed)
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
		if constexpr (DEBUG_CLASS)
		{
			Console::writeLine({ "Key[", std::to_string(button), "] updated to ", (pressed ? "down" : "up") });
		}
	}

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	inline void Controllerhandler<Index, Axis, AxisValue, Button>::updateAxis(Controller & controller, Axis const & axis, AxisValue const & axisValue)
	{
		constexpr auto max = static_cast<double>(std::numeric_limits<AxisValue>::max());
		constexpr auto min = static_cast<double>(std::numeric_limits<AxisValue>::min());
		auto const & value = static_cast<double>(axisValue);
		static_assert(max != min, "ERROR: in 'Controllerhandler<Index, Axis, AxisValue, Button>::updateAxis' Max cannot be the same as Min");
		auto const result = (((value - min) / (max - min)) * 2.0) - 1.0 ;
		if (auto const & itt = controller.axisMap.find(axis); itt != controller.axisMap.end())
			itt->second = result;
		else
			controller.axisMap.insert({ axis, result });
		if constexpr (DEBUG_CLASS)
		{
			Console::writeLine({ "Axis[", std::to_string(axis), "] updated to [", std::to_string(axisValue), "]" });
		}
	}

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	inline bool Controllerhandler<Index, Axis, AxisValue, Button>::isButtonDown(ButtonMap const & map, Button const & button)
	{
		const auto predicate = [&button](ButtonPair const & p) constexpr { return p.first == button && p.second; };
		return std::find_if(map.begin(), map.end(), predicate) != map.end();
	}

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	inline bool Controllerhandler<Index, Axis, AxisValue, Button>::isButtonDown(ButtonMap const & map, std::initializer_list<Button> const & buttons)
	{
		const auto predicate = [&buttons](ButtonPair const & p) constexpr
		{
			return p.second &&
				std::find_if(buttons.begin(), buttons.end(), [&p](Button const & button) constexpr { return p.first == button; }) != buttons.end();
		};
		return std::find_if(map.begin(), map.end(), predicate) != map.end();
	}

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	inline bool Controllerhandler<Index, Axis, AxisValue, Button>::isButtonUp(ButtonMap const & map, Button const & button)
	{
		const auto predicate = [&button](ButtonPair const & p) constexpr { return p.first == button && !p.second; };
		return std::find_if(map.begin(), map.end(), predicate) != map.end();
	}

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	inline bool Controllerhandler<Index, Axis, AxisValue, Button>::isButtonUp(ButtonMap const & map, std::initializer_list<Button> const & buttons)
	{
		const auto predicate = [&buttons](ButtonPair const & p) constexpr
		{
			return !p.second &&
				std::find_if(buttons.begin(), buttons.end(), [&p](Button const & button) constexpr { return p.first == button; }) != buttons.end();
		};
		return std::find_if(map.begin(), map.end(), predicate) != map.end();
	}

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	inline bool Controllerhandler<Index, Axis, AxisValue, Button>::isAxisOver(ButtonMap const & map, ButtonMap const & prevMap, Button const & button)
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

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	inline bool Controllerhandler<Index, Axis, AxisValue, Button>::isAxisOver(ButtonMap const & map, ButtonMap const & prevMap, std::initializer_list<Button> const & buttons)
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

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	inline bool Controllerhandler<Index, Axis, AxisValue, Button>::isButtonUnpressed(ButtonMap const & map, ButtonMap const & prevMap, Button const & button)
	{
		if (auto const & itt = map.find(button); itt != map.end())
		{
			if (auto const & prevItt = prevMap.find(itt->first); prevItt != prevMap.end())
				return !itt->second && prevItt->second;
			else
				return !itt->second;
		}
		return false;
	}

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	inline bool Controllerhandler<Index, Axis, AxisValue, Button>::isButtonUnpressed(ButtonMap const & map, ButtonMap const & prevMap, std::initializer_list<Button> const & buttons)
	{
		for (auto const &[mapKey, mapValue] : map)
		{
			if (std::find(buttons.begin(), buttons.end(), mapKey) == buttons.end())
				continue;
			if (auto const & result = prevMap.find(mapKey); result != prevMap.end())
				return !mapValue && result->second;
			return !mapValue;
		}
		return false;
	}

	template<typename Index, typename Axis, typename AxisValue, typename Button>
	inline double Controllerhandler<Index, Axis, AxisValue, Button>::getAxis(AxisMap const & map, Axis const & axis)
	{
		if (auto const & itt = map.find(axis); itt != map.end())
			return itt->second;
		else
			return 0.0;
	}
}

#endif // !_INPUT_CONTROLLER_HANDLER_H
