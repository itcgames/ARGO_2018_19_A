#ifndef _UTILITIES_VECTOR_H
#define _UTILITIES_VECTOR_H

namespace app::util
{
	/// 
	/// @brief Constructs a vector using only move semantics.
	/// @author Rafael Plugge
	/// 
	/// <summary>
	/// Since the standard library doesn't contain a move constructor when using initializer list,
	/// using this special function the objects will be moved when inside the initializer list,
	/// allowing for non-copyable objects to be initialized into a vector using a initializer list.
	/// </summary>
	template<typename T>
	std::vector<T> make_vector(std::initializer_list<T> const & list)
	{
		return std::vector<T>(std::make_move_iterator(const_cast<T*>(list.begin())), std::make_move_iterator(const_cast<T*>(list.end())));
	}

	template<typename _Key, typename _Value>
	std::map<_Key, _Value> make_map(std::initializer_list<std::pair<_Key, _Value>> const & list)
	{
		using pair = std::pair<_Key, _Value>;
		return std::map<_Key, _Value>(std::make_move_iterator(const_cast<pair*>(list.begin())), std::make_move_iterator(const_cast<pair*>(list.end())));
	}

	template<typename _Key, typename _Value>
	std::unordered_map<_Key, _Value> make_unordered_map(std::initializer_list<std::pair<_Key, _Value>> const & list)
	{
		using pair = std::pair<_Key, _Value>;
		return std::unordered_map<_Key, _Value>(std::make_move_iterator(const_cast<pair*>(list.begin())), std::make_move_iterator(const_cast<pair*>(list.end())));
	}
}

#endif // !_UTILITIES_VECTOR_H
