#ifndef _APP_INPUT_MOUSEHANDLER_H
#define _APP_INPUT_MOUSEHANDLER_H

#include "math/Vector2.h"

namespace app::inp
{
	/// 
	/// @brief Mousehandler input class.
	/// @author Rafael Plugge
	/// 
	/// This class will handle input of mouse buttons
	/// and track the mouse's position.
	/// 
	template<typename ButtonType>
	class Mousehandler
	{
	private: // Private typedefs
	public: // Constructors/Destructor/Assignments
		Mousehandler() = default;
		Mousehandler(Mousehandler<ButtonType> const &) = default;
		Mousehandler(Mousehandler<ButtonType> &&) = default;

		~Mousehandler() = default;

		Mousehandler<ButtonType> & operator=(Mousehandler<ButtonType> const &) = default;
		Mousehandler<ButtonType> & operator=(Mousehandler<ButtonType> &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		void updateButton(ButtonType const & button, bool const & pressed);
		void updatePosition(std::int32_t const & x, std::int32_t const & y);
		void update();

		bool isButtonDown(ButtonType const & button) const;
		bool isButtonDown(std::initializer_list<ButtonType> const & buttons) const;
		bool isButtonUp(ButtonType const & button) const;
		bool isButtonUp(std::initializer_list<ButtonType> const & buttons) const;
		bool isButtonPressed(ButtonType const & button) const;
		bool isButtonPressed(std::initializer_list<ButtonType> const & buttons) const;
		constexpr math::Vector2i const getPosition() const { return m_mouse; }
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
		static bool isButtonDown(std::map<const ButtonType, bool> const & keyMap, ButtonType const & button);
		static bool isButtonDown(std::map<const ButtonType, bool> const & keyMap, std::initializer_list<ButtonType> const & buttons);
		static bool isButtonUp(std::map<const ButtonType, bool> const & keyMap, ButtonType const & button);
		static bool isButtonUp(std::map<const ButtonType, bool> const & keyMap, std::initializer_list<ButtonType> const & buttons);
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
		std::map<const ButtonType, bool> m_keyNowMap;
		std::map<const ButtonType, bool> m_keyPrevMap;
		math::Vector2i m_mouse = { 0, 0 };
	};

	#pragma region Implementation

	template<typename ButtonType>
	void app::inp::Mousehandler<ButtonType>::updateButton(ButtonType const & button, bool const & pressed)
	{
		if (auto const & itt = m_keyNowMap.find(button); itt != m_keyNowMap.end())
		{
			auto &[key, value] = *itt;
			value = pressed;
		}
		else
		{
			m_keyNowMap.insert({ button, pressed });
			m_keyPrevMap.insert({ button, !pressed });
		}
	}

	template<typename ButtonType>
	void app::inp::Mousehandler<ButtonType>::updatePosition(std::int32_t const & x, std::int32_t const & y)
	{
		m_mouse.x = x;
		m_mouse.y = y;
	}

	template<typename ButtonType>
	void app::inp::Mousehandler<ButtonType>::update()
	{
		m_keyPrevMap = m_keyNowMap;
	}

	template<typename ButtonType>
	bool app::inp::Mousehandler<ButtonType>::isButtonDown(ButtonType const & button) const
	{
		return app::inp::Mousehandler<ButtonType>::isButtonDown(m_keyNowMap, button);
	}

	template<typename ButtonType>
	bool app::inp::Mousehandler<ButtonType>::isButtonDown(std::initializer_list<ButtonType> const & buttons) const
	{
		return app::inp::Mousehandler<ButtonType>::isButtonDown(m_keyNowMap, buttons);
	}

	template<typename ButtonType>
	bool app::inp::Mousehandler<ButtonType>::isButtonUp(ButtonType const & button) const
	{
		return app::inp::Mousehandler<ButtonType>::isButtonUp(m_keyNowMap, button);
	}

	template<typename ButtonType>
	bool app::inp::Mousehandler<ButtonType>::isButtonUp(std::initializer_list<ButtonType> const & buttons) const
	{
		return app::inp::Mousehandler<ButtonType>::isButtonUp(m_keyNowMap, buttons);
	}

	template<typename ButtonType>
	bool app::inp::Mousehandler<ButtonType>::isButtonPressed(ButtonType const & button) const
	{
		return app::inp::Mousehandler<ButtonType>::isButtonUp(m_keyPrevMap, button)
			&& app::inp::Mousehandler<ButtonType>::isButtonDown(m_keyNowMap, button);
	}

	template<typename ButtonType>
	bool app::inp::Mousehandler<ButtonType>::isButtonPressed(std::initializer_list<ButtonType> const & buttons) const
	{
		for (auto const &[mapKey, mapValue] : m_keyNowMap)
		{
			// if the current map key is not in the list of buttons to check, skip it
			if (std::find_if(buttons.begin(), buttons.end(), [&mapKey](ButtonType const & button) { return mapKey == button; }) == buttons.end()) { continue; }
			if (auto const & prevItt = m_keyPrevMap.find(mapKey); prevItt != m_keyPrevMap.end())
			{
				auto const &[prevKey, prevValue] = *prevItt;
				return mapValue && !prevValue;
			}
			return mapValue;
		}
		return false;
	}

	template<typename ButtonType>
	inline bool app::inp::Mousehandler<ButtonType>::isButtonDown(std::map<const ButtonType, bool> const & keyMap, ButtonType const & button)
	{
		using pair = std::pair<const ButtonType, bool>;
		const auto predicate = [&button](pair const & p) constexpr { return p.first == button && p.second; };
		return std::find_if(keyMap.begin(), keyMap.end(), predicate) != keyMap.end();
	}

	template<typename ButtonType>
	inline bool app::inp::Mousehandler<ButtonType>::isButtonDown(std::map<const ButtonType, bool> const & keyMap, std::initializer_list<ButtonType> const & buttons)
	{
		using pair = std::pair<const ButtonType, bool>;
		const auto predicate = [&buttons](pair const & p) constexpr
		{
			return p.second &&
				std::find_if(buttons.begin(), buttons.end(), [&p](ButtonType const & button) constexpr { return p.first == button; }) != buttons.end();
		};
		return std::find_if(keyMap.begin(), keyMap.end(), predicate) != keyMap.end();
	}

	template<typename ButtonType>
	inline bool app::inp::Mousehandler<ButtonType>::isButtonUp(std::map<const ButtonType, bool> const & keyMap, ButtonType const & button)
	{
		using pair = std::pair<const ButtonType, bool>;
		const auto predicate = [&button](pair const & p) constexpr { return p.first == button && !p.second; };
		return std::find_if(keyMap.begin(), keyMap.end(), predicate) != keyMap.end();
	}

	template<typename ButtonType>
	inline bool app::inp::Mousehandler<ButtonType>::isButtonUp(std::map<const ButtonType, bool> const & keyMap, std::initializer_list<ButtonType> const & buttons)
	{
		using pair = std::pair<const ButtonType, bool>;
		const auto predicate = [&buttons](pair const & p) constexpr
		{
			return !p.second &&
				std::find_if(buttons.begin(), buttons.end(), [&p](ButtonType const & button) constexpr { return p.first == button; }) != buttons.end();
		};
		return std::find_if(keyMap.begin(), keyMap.end(), predicate) != keyMap.end();
	}

	#pragma endregion
}

#endif // !_APP_INPUT_MOUSEHANDLER_H
