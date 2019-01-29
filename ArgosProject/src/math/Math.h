#ifndef _MATH_H
#define _MATH_H

namespace app::math
{
	template<typename T> constexpr T pi() { return static_cast<T>(std::acos(-1.0)); }
	template<typename T> constexpr T toRadians(T const & rad) { return static_cast<T>(rad * (pi<T>() / static_cast<T>(180))); }
	template<typename T> constexpr T toDegrees(T const & deg) { return static_cast<T>(deg * (static_cast<T>(180) / pi<T>())); }
	template<typename T> constexpr math::Vector2<T> rotate(math::Vector2<T> const & v, T angle) { return rotateRad(v, math::toRadians(angle)); }
	template<typename T> constexpr math::Vector2<T> rotateRad(math::Vector2<T> const & v, T rad)
	{
		const auto cosine = static_cast<T>(std::cos(rad));
		const auto sine = static_cast<T>(std::sin(rad));
		return math::Vector2<T> {
			v.x * cosine - v.y * sine,
			v.x * sine + v.y * cosine
		};
		return rotateAroundRad(v, rad, math::Vector2<T>{});
	}
	template<typename T> constexpr math::Vector2<T> rotateAround(math::Vector2<T> const & v, T angle, math::Vector2<T> const & point) { return rotateAroundRad(v, math::toRadians(angle), point); }
	template<typename T> constexpr math::Vector2<T> rotateAroundRad(math::Vector2<T> const & v, T rad, math::Vector2<T> const & point)
	{
		const auto cosine = static_cast<T>(std::cos(rad));
		const auto sine = static_cast<T>(std::sin(rad));
		return math::Vector2<T> {
			((v.x - point.x) * cosine) - ((point.y - v.y) * sine) + point.x,
			((point.y - v.y) * cosine) - ((v.x - point.x) * sine) + point.y
		};
	}
}

#endif // !_MATH_H
