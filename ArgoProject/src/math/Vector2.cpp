#include "stdafx.h"
#include "Vector2.h"

template<typename T>
app::math::Vector2<T>::Vector2()
	: x(zero)
	, y(zero)
{
}

template<typename T>
app::math::Vector2<T>::Vector2(T const & _x, T const & _y)
	: x(_x)
	, y(_y)
{
}

/************************************************************************/
/*************************** Member functions ***************************/
/************************************************************************/

template<typename T>
app::math::Vector2<T> const app::math::Vector2<T>::unit(Vector2<T> const & v)
{
	auto const length = v.magnitude();
	assert(length != app::math::Vector2<T>::zero);
	return Vector2<T>(v.x / length, v.y / length);
}

template<typename T>
T app::math::Vector2<T>::dot(Vector2<T> const & left, Vector2<T> const & right)
{
	return (left.x * right.x) + (left.y * right.y);
}

template<typename T>
T app::math::Vector2<T>::det(Vector2<T> const & left, Vector2<T> const & right)
{
	return (left.x * right.y) - (left.y * right.x);
}

template<typename T>
T app::math::Vector2<T>::angleBetween(Vector2<T> const & left, Vector2<T> const & right)
{
	return static_cast<T>(math::toDegrees(std::atan2(Vector2<T>::det(left, right), Vector2<T>::dot(left, right))));
}

template<typename T>
app::math::Vector2<T> & app::math::Vector2<T>::operator=(T const & t)
{
	this->x = t;
	this->y = t;
	return *this;
}

template<typename T>
app::math::Vector2<T> & app::math::Vector2<T>::operator+=(Vector2 const & v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

template<typename T>
app::math::Vector2<T> & app::math::Vector2<T>::operator+=(T const & t)
{
	this->x += t;
	this->y += t;
	return *this;
}

template<typename T>
app::math::Vector2<T> & app::math::Vector2<T>::operator-=(Vector2 const & v)
{
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

template<typename T>
app::math::Vector2<T> & app::math::Vector2<T>::operator-=(T const & t)
{
	this->x -= t;
	this->y -= t;
	return *this;
}

template<typename T>
app::math::Vector2<T> & app::math::Vector2<T>::operator*=(Vector2 const & v)
{
	this->x *= v.x;
	this->y *= v.y;
	return *this;
}

template<typename T>
app::math::Vector2<T> & app::math::Vector2<T>::operator*=(T const & t)
{
	this->x *= t;
	this->y *= t;
	return *this;
}

template<typename T>
app::math::Vector2<T> & app::math::Vector2<T>::operator/=(Vector2 const & v)
{
	assert(v.x != app::math::Vector2<T>::zero && v.y != app::math::Vector2<T>::zero);
	this->x /= v.x;
	this->y /= v.y;
	return *this;
}

template<typename T>
app::math::Vector2<T> & app::math::Vector2<T>::operator/=(T const & t)
{
	assert(t != app::math::Vector2<T>::zero);
	this->x /= t;
	this->y /= t;
	return *this;
}

template<typename T>
T app::math::Vector2<T>::magnitudeSqr() const
{
	return (this->x * this->x) + (this->y * this->y);
}

template<typename T>
T app::math::Vector2<T>::magnitude() const
{
	return static_cast<T>(std::sqrt(magnitudeSqr()));
}

template<typename T>
app::math::Vector2<T>& app::math::Vector2<T>::truncate(T max)
{
	if (this->magnitude() > max)
	{
		(*this) = this->unit() * max;
	}
	return *this;
}

template<typename T>
app::math::Vector2<T> & app::math::Vector2<T>::unit()
{
	auto const length = this->magnitude();
	assert(length != app::math::Vector2<T>::zero);
	this->x /= length;
	this->y /= length;
	return *this;
}

template<typename T>
app::math::Vector2<T> app::math::Vector2<T>::unit() const
{
	auto const length = this->magnitude();
	assert(length != app::math::Vector2<T>::zero);
	return Vector2<T>(this->x, this->y) / length;
}

template<typename T>
T app::math::Vector2<T>::dot(app::math::Vector2<T> const & other) const
{
	return app::math::Vector2<T>::dot(*this, other);
}

template<typename T>
T app::math::Vector2<T>::det(Vector2<T> const & other) const
{
	return app::math::Vector2<T>::det(*this, other);
}

template<typename T>
T app::math::Vector2<T>::toAngle() const
{
	return static_cast<T>(math::toDegrees(std::atan2(this->x, this->y)));
}

template<typename T>
T app::math::Vector2<T>::angleBetween(Vector2<T> const & other) const
{
	return app::math::Vector2<T>::angleBetween(*this, other);
}

template<typename T>
app::math::Vector2<T>::operator std::string() const
{
	return std::to_string(this->x) + ", " + std::to_string(this->y);
}

template class app::math::Vector2<double>;
template class app::math::Vector2<float>;
template class app::math::Vector2<int32_t>;
template class app::math::Vector2<uint32_t>;
