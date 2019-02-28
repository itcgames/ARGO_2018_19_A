#ifndef _APP_MATH_VECTOR2_H
#define _APP_MATH_VECTOR2_H

namespace app::math
{
	/// 
	/// @brief 2 dimensional vector class.
	/// @author Rafael Plugge
	/// 
	/// Handles all mathematics behind 2 dimensional vectors.
	/// 
	template<typename T>
	class Vector2
	{
	public: // Constructors/Destructor/Assignments
		Vector2();
		Vector2(T const & _x, T const & _y);
		template<typename O>
		Vector2(O const & _x, O const & _y);
		template<typename O>
		Vector2(Vector2<O> const & v);

		~Vector2() = default;

		Vector2(Vector2 const &) = default;
		Vector2 & operator=(Vector2 const &) = default;

		Vector2(Vector2 &&) = default;
		Vector2 & operator=(Vector2 &&) = default;

	public: // Public Static Functions
		static Vector2<T> const unit(Vector2<T> const & v);
		static T dot(Vector2<T> const & left, Vector2<T> const & right);
		static T det(Vector2<T> const & left, Vector2<T> const & right);
		static T angleBetween(Vector2<T> const & left, Vector2<T> const & right);

	public: // Public Member Functions
		Vector2 & operator=(T const & t);

		Vector2 & operator+=(Vector2 const & v);
		Vector2 & operator+=(T const & t);

		Vector2 & operator-=(Vector2 const & v);
		Vector2 & operator-=(T const & t);

		Vector2 & operator*=(Vector2 const & v);
		Vector2 & operator*=(T const & t);

		Vector2 & operator/=(Vector2 const & v);
		Vector2 & operator/=(T const & t);

		constexpr bool operator==(Vector2 const & v) const;
		constexpr bool operator==(T const & t) const;

		constexpr bool operator!=(Vector2 const & v) const;
		constexpr bool operator!=(T const & t) const;

		constexpr bool operator<(Vector2 const & v) const;
		constexpr bool operator<(T const & t) const;

		constexpr bool operator>(Vector2 const & v) const;
		constexpr bool operator>(T const & t) const;

		constexpr bool operator<=(Vector2 const & v) const;
		constexpr bool operator<=(T const & t) const;

		constexpr bool operator>=(Vector2 const & v) const;
		constexpr bool operator>=(T const & t) const;

		T magnitudeSqr() const;
		T magnitude() const;
		Vector2<T> & truncate(T max);
		Vector2<T> & unit();
		Vector2<T> unit() const;
		T dot(Vector2<T> const & other) const;
		T det(Vector2<T> const & other) const;
		T toAngle() const;
		T angleBetween(Vector2<T> const & other) const;

		operator std::string() const;

	public: // Public Static Variables
		constexpr static T const zero = static_cast<T>(0u);
	public: // Public Member Variables
		T x, y;
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};

	template<typename T>
	template<typename O>
	app::math::Vector2<T>::Vector2(O const & _x, O const & _y)
		: x(static_cast<T>(_x))
		, y(static_cast<T>(_y))
	{
	}

	template<typename T>
	template<typename O>
	app::math::Vector2<T>::Vector2(Vector2<O> const & v)
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(v.y))
	{
	}

	// Plus operators

	template<typename T> Vector2<T> operator+(Vector2<T> leftV, Vector2<T> const & rightV)
	{
		leftV.x += rightV.x; leftV.y += rightV.y;
		return leftV;
	}
	template<typename T> Vector2<T> operator+(Vector2<T> v, T const & t)
	{
		v.x += t; v.y += t;
		return v;
	}
	template<typename T> Vector2<T> operator+(T const & t, Vector2<T> v)
	{
		v.x += t; v.y += t;
		return v;
	}

	// Minus operators

	template<typename T> Vector2<T> operator-(Vector2<T> leftV, Vector2<T> const & rightV)
	{
		leftV.x -= rightV.x; leftV.y -= rightV.y;
		return leftV;
	}
	template<typename T> Vector2<T> operator-(Vector2<T> v, T const & t)
	{
		v.x -= t; v.y -= t;
		return v;
	}
	template<typename T> Vector2<T> operator-(T const & t, Vector2<T> v)
	{
		v.x -= t; v.y -= t;
		return v;
	}

	// Negate operator

	template<typename T> Vector2<T> operator-(Vector2<T> v)
	{
		v.x = -v.x; v.y = -v.y;
		return v;
	}

	// Multiplication operators

	template<typename T> Vector2<T> operator*(Vector2<T> leftV, Vector2<T> const & rightV)
	{
		leftV.x *= rightV.x; leftV.y *= rightV.y;
		return leftV;
	}
	template<typename T> Vector2<T> operator*(Vector2<T> v, T const & t)
	{
		v.x *= t; v.y *= t;
		return v;
	}
	template<typename T> Vector2<T> operator*(T const & t, Vector2<T> v)
	{
		v.x *= t; v.y *= t;
		return v;
	}

	// Division operators

	template<typename T> Vector2<T> operator/(Vector2<T> leftV, Vector2<T> const & rightV)
	{
		assert(rightV.x != app::math::Vector2<T>::zero && rightV.y != app::math::Vector2<T>::zero);
		leftV.x /= rightV.x; leftV.y /= rightV.y;
		return leftV;
	}
	template<typename T> Vector2<T> operator/(Vector2<T> v, T const & t)
	{
		assert(t != app::math::Vector2<T>::zero);
		v.x /= t; v.y /= t;
		return v;
	}
	template<typename T> Vector2<T> operator/(T const & t, Vector2<T> v)
	{
		assert(v.x != app::math::Vector2<T>::zero && v.y != app::math::Vector2<T>::zero);
		v.x = t / v.x; v.y = t / v.y;
		return v;
	}

	// Equality operators

	template<typename T> constexpr bool operator==(Vector2<T> const & leftV, Vector2<T> const & rightV)
	{
		return leftV.x == rightV.x && leftV.y == rightV.y;
	}
	template<typename T> constexpr bool operator==(Vector2<T> const & v, T const & t)
	{
		return v.x == t && v.y == t;
	}
	template<typename T> constexpr bool operator==(T const & t, Vector2<T> const & v)
	{
		return t == v.x && t == v.y;
	}

	// Inequality operators

	template<typename T> constexpr bool operator!=(Vector2<T> const & leftV, Vector2<T> const & rightV)
	{
		return leftV.x != rightV.x && leftV.y == rightV.y;
	}
	template<typename T> constexpr bool operator!=(Vector2<T> const & v, T const & t)
	{
		return v.x != t && v.y != t;
	}
	template<typename T> constexpr bool operator!=(T const & t, Vector2<T> const & v)
	{
		return t != v.x && t != v.y;
	}

	typedef Vector2<double> Vector2d;
	typedef Vector2<float> Vector2f;
	typedef Vector2<int32_t> Vector2i;
	typedef Vector2<uint32_t> Vector2u;
}

#endif // !_APP_MATH_VECTOR2_H
