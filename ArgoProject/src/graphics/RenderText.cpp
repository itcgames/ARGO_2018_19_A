#include "stdafx.h"
#include "RenderText.h"

app::gra::RenderText & app::gra::RenderText::setFont(std::shared_ptr<app::gra::Font> font)
{
	m_font = font;
	return *this;
}

app::gra::RenderText & app::gra::RenderText::setSourceRect(std::optional<SDL_Rect> const & rect)
{
	m_sourceRect = rect;
	return *this;
}

app::gra::RenderText & app::gra::RenderText::setPosition(app::math::Vector2d const & position)
{
	m_position = position;
	return *this;
}

app::gra::RenderText & app::gra::RenderText::setRotation(double const & rotation)
{
	m_rotation = rotation;
	return *this;
}

app::gra::RenderText & app::gra::RenderText::setOrigin(app::math::Vector2d const & origin)
{
	m_origin = origin;
	return *this;
}

app::gra::RenderText & app::gra::RenderText::setSize(app::math::Vector2d const & size)
{
	m_size = size;
	return *this;
}

app::gra::RenderText & app::gra::RenderText::setText(std::string const & text)
{
	if (m_text.capacity() < text.size()) { m_text.reserve(text.size()); }
	m_text = text;
	this->render();
	return *this;
}

app::gra::RenderText & app::gra::RenderText::setColor(SDL_Color const & color)
{
	m_color = color;
	return *this;
}

app::gra::RenderText & app::gra::RenderText::render()
{
	if (!m_font) { throw std::exception("ERROR: Font not loaded"); }
	m_font->prepare(m_quality, m_text, m_color);
	return *this;
}
