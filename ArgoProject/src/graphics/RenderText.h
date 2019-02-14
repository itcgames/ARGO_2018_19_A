#ifndef _GRAPHICS_RENDER_TEXT_H
#define _GRAPHICS_RENDER_TEXT_H

#include "Font.h"

namespace app::gra
{
	class RenderText
	{
	public: // Constructors/Destructor/Assignments
		RenderText() = default;
		~RenderText() = default;

		RenderText(RenderText const &) = default;
		RenderText & operator=(RenderText const &) = default;

		RenderText(RenderText &&) = default;
		RenderText & operator=(RenderText &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		constexpr TTF_Font * getFont() const { return m_font ? m_font->get() : nullptr; }
		SDL_Texture * getTexture() const { return m_font->getTexture(); }
		constexpr app::gra::Font::Quality const & getQuality() const { return m_quality; }
		constexpr std::optional<SDL_Rect> const & getSourceRect() const { return m_sourceRect; }
		constexpr math::Vector2d const & getPosition() const { return m_position; }
		constexpr double const & getRotation() const { return m_rotation; }
		constexpr math::Vector2d const & getOrigin() const { return m_origin; }
		constexpr math::Vector2d const & getSize() const { return m_size; }
		constexpr std::string const & getText() const { return m_text; }
		constexpr SDL_Color const & getColor() const { return m_color; }

		RenderText & setFont(std::shared_ptr<app::gra::Font> font);
		RenderText & setSourceRect(std::optional<SDL_Rect> const & rect);
		RenderText & setPosition(app::math::Vector2d const & position);
		RenderText & setRotation(double const & rotation);
		RenderText & setOrigin(app::math::Vector2d const & origin);
		RenderText & setSize(app::math::Vector2d const & size);
		RenderText & setText(std::string const & text);
		RenderText & setColor(SDL_Color const & color);

		RenderText & render();
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
		std::shared_ptr<app::gra::Font> m_font;
		app::gra::Font::Quality m_quality = app::gra::Font::Quality::Blended;
		std::optional<SDL_Rect> m_sourceRect;
		math::Vector2d m_position;
		math::Vector2d m_origin;
		math::Vector2d m_size;
		double m_rotation;
		std::string m_text;
		SDL_Color m_color;
	};
}

#endif // !_GRAPHICS_RENDER_TEXT_H
