#ifndef _APP_INPUT_KEYHANDLER_H
#define _APP_INPUT_KEYHANDLER_H

namespace app::inp
{
	/// 
	/// @brief KeyHandler input class.
	/// @author Rafael Plugge
	/// 
	/// This class will handle input of keys.
	/// 
	template<typename KeyType>
	class Keyhandler
	{
	public: // Constructors/Destructor/Assignments
		Keyhandler() = default;
		~Keyhandler() = default;

		Keyhandler(Keyhandler const &) = default;
		Keyhandler & operator=(Keyhandler const &) = default;

		Keyhandler(Keyhandler &&) = default;
		Keyhandler & operator=(Keyhandler &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		void updateKey(KeyType const & key, bool const & pressed);
		void update();

		bool isKeyDown(KeyType const & key) const;
		bool isKeyDown(std::initializer_list<KeyType> const & keys) const;
		bool isKeyUp(KeyType const & key) const;
		bool isKeyUp(std::initializer_list<KeyType> const & key) const;
		bool isKeyPressed(KeyType const & key) const;
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
		std::map<const KeyType, bool> m_keyNowMap;
		std::map<const KeyType, bool> m_keyPrevMap;
	};

	#pragma region Implementation


	template<typename KeyType>
	void app::inp::Keyhandler<KeyType>::updateKey(KeyType const & key, bool const & pressed)
	{
		if (auto itt = m_keyNowMap.find(key); itt != m_keyNowMap.end())
		{
			auto &[key, value] = *itt;
			value = pressed;
		}
		else
		{
			m_keyNowMap.insert({ key, pressed });
			m_keyPrevMap.insert({ key, !pressed });
		}
	}

	template<typename KeyType>
	void app::inp::Keyhandler<KeyType>::update()
	{
		m_keyPrevMap = m_keyNowMap;
	}

	template<typename KeyType>
	bool app::inp::Keyhandler<KeyType>::isKeyDown(KeyType const & key) const
	{
		if (auto const & itt = m_keyNowMap.find(key); itt != m_keyNowMap.end())
		{
			auto const &[key, value] = *itt;
			return value;
		}
		return false;
	}

	template<typename KeyType>
	bool app::inp::Keyhandler<KeyType>::isKeyDown(std::initializer_list<KeyType> const & keys) const
	{
		for (auto const &[mapKey, mapValue] : m_keyNowMap)
		{
			if (mapValue && std::find(keys.begin(), keys.end(), mapKey) != keys.end()) { return true; }
		}
		return false;
	}

	template<typename KeyType>
	bool app::inp::Keyhandler<KeyType>::isKeyUp(KeyType const & key) const
	{
		if (auto const & itt = m_keyNowMap.find(key); itt != m_keyNowMap.end())
		{
			auto const &[key, value] = *itt;
			return !value;
		}
		return false;
	}

	template<typename KeyType>
	bool app::inp::Keyhandler<KeyType>::isKeyUp(std::initializer_list<KeyType> const & keys) const
	{
		for (auto const &[mapKey, mapValue] : m_keyNowMap)
		{
			if (!mapValue && std::find(keys.begin(), keys.end(), mapKey) != keys.end()) { return true; }
		}
		return false;
	}

	template<typename KeyType>
	bool app::inp::Keyhandler<KeyType>::isKeyPressed(KeyType const & keyPressed) const
	{
		if (auto const & itt = m_keyNowMap.find(keyPressed); itt != m_keyNowMap.end())
		{
			auto const &[key, value] = *itt;

			if (auto const & prevItt = m_keyPrevMap.find(key); prevItt != m_keyPrevMap.end())
			{
				auto const &[prevKey, prevValue] = *prevItt;
				return value && !prevValue;
			}
			return value;
		}
		return false;
	}


	#pragma endregion

}
#endif
