#ifndef _UTIL_TIME_H
#define _UTIL_TIME_H

namespace app::time
{
	/// 
	/// @brief Alias for the chronos standard library of seconds using float as the counting type.
	/// 
	/// <summary>
	/// Redefines the standard libraries chrono seconds template type to be the standard seconds ratio with counting type of float,
	/// this is because internally the standard library stores the duration in maximum precision and converts upwards utilising the two template arguments,
	/// first one being float and the second one being hidden as the standard ratio (defaults to std::ratio of 1i64 to 1i64) for a 64 bit integer to represent seconds.
	/// </summary>
	typedef std::chrono::duration<float> seconds;

	/// 
	/// @brief Alias for the chronos standard library of milliseconds.
	/// 
	/// <summary>
	/// Redefines the standard libraries chrono milliseconds type definition in order to shorten the type, as in not need to type the external namespaces, and standardise the milliseconds definition accross the project.
	/// </summary>
	typedef std::chrono::milliseconds milliseconds;

	/// 
	/// @brief Alias for the chronos standard library of microseconds.
	/// 
	/// <summary>
	/// Redefines the standard libraries chrono microseconds type definition in order to shorten the type, as in not need to type the external namespaces, and standardise the microseconds definition accross the project.
	/// </summary>
	typedef std::chrono::microseconds microseconds;

	/// 
	/// @brief Alias for the chronos standard library of nanoseconds.
	/// 
	/// <summary>
	/// Redefines the standard libraries chrono nanoseconds type definition in order to shorten the type, as in not need to type the external namespaces, and standardise the nanoseconds definition accross the project.
	/// </summary>
	typedef std::chrono::nanoseconds nanoseconds;

	/// 
	/// @brief Converts passed time of type T into app::time::seconds.
	/// 
	/// <summary>
	/// Utilizes standard library chronos duration cast to convert from type T into app::time::seconds.
	/// </summary>
	/// <param name="time">read-only reference to the original time value to be converted to type app::time::seconds.</param>
	/// <typeparam name="T">Custom type that is castable to app::time::seconds or only other acceptable types are app::time::seconds, app::time::milliseconds, app::time::microseconds and app::time::nanoseconds</typeparam>
	/// <returns>newly created app::time::seconds, this conversion is done via constexpr meaning its done at compile time if possible.</returns>
	template<typename T>
	constexpr app::time::seconds toSeconds(T const & time) { return std::chrono::duration_cast<app::time::seconds>(time); }

	/// 
	/// @brief Converts passed time of type T into app::time::milliseconds
	/// 
	/// <summary>
	/// Utilizes standard library chronos duration cast to convert from type T into app::time::milliseconds.
	/// </summary>
	/// <param name="time">read-only reference to the original time value to be converted to type app::time::milliseconds.</param>
	/// <typeparam name="T">Custom type that is castable to app::time::milliseconds or only other acceptable types are app::time::seconds, app::time::milliseconds, app::time::microseconds and app::time::nanoseconds</typeparam>
	/// <returns>newly created app::time::milliseconds, this conversion is done via constexpr meaning its done at compile time if possible.</returns>
	template<typename T>
	constexpr app::time::milliseconds toMillis(T const & time) { return std::chrono::duration_cast<app::time::milliseconds>(time); }

	/// 
	/// @brief Converts passed time of type T into app::time::microseconds
	/// 
	/// <summary>
	/// Utilizes standard library chronos duration cast to convert from type T into app::time::microseconds.
	/// </summary>
	/// <param name="time">read-only reference to the original time value to be converted to type app::time::microseconds.</param>
	/// <typeparam name="T">Custom type that is castable to app::time::microseconds or only other acceptable types are app::time::seconds, app::time::milliseconds, app::time::microseconds and app::time::nanoseconds</typeparam>
	/// <returns>newly created app::time::microseconds, this conversion is done via constexpr meaning its done at compile time if possible.</returns>
	template<typename T>
	constexpr app::time::microseconds toMicros(T const & time) { return std::chrono::duration_cast<app::time::microseconds>(time); }

	/// 
	/// @brief Converts passed time of type T into app::time::nanoseconds
	/// 
	/// <summary>
	/// Utilizes standard library chronos duration cast to convert from type T into app::time::nanoseconds.
	/// </summary>
	/// <param name="time">read-only reference to the original time value to be converted to type app::time::nanoseconds.</param>
	/// <typeparam name="T">Custom type that is castable to app::time::nanoseconds or only other acceptable types are app::time::seconds, app::time::milliseconds, app::time::microseconds and app::time::nanoseconds</typeparam>
	/// <returns>newly created app::time::nanoseconds, this conversion is done via constexpr meaning its done at compile time if possible.</returns>
	template<typename T>
	constexpr app::time::nanoseconds toNanos(T const & time) { return std::chrono::duration_cast<app::time::nanoseconds>(time); }

}

#endif // !_UTIL_TIME_H
