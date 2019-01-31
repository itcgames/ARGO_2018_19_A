#include "stdafx.h"
#include "RenderRect.h"

app::gra::RenderRect & app::gra::RenderRect::setTexture(std::shared_ptr<app::gra::Texture> texture)
{
	m_texture = texture;
	return *this;
}

app::gra::RenderRect & app::gra::RenderRect::setPosition(app::math::Vector2f const & position)
{
	m_position = position;
	return *this;
}

app::gra::RenderRect & app::gra::RenderRect::setRotation(double const & rotation)
{
	m_rotation = rotation;
	return *this;
}

app::gra::RenderRect & app::gra::RenderRect::setOrigin(app::math::Vector2d const & origin)
{
	m_origin = origin;
	return *this;
}

app::gra::RenderRect & app::gra::RenderRect::setSize(app::math::Vector2d const & size)
{
	m_size = size;
	return *this;
}
