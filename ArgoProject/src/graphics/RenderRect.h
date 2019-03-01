#ifndef _GRAPHICS_RENDER_RECT_H
#define _GRAPHICS_RENDER_RECT_H

#include "graphics/Texture.h"

namespace app::gra
{
	class RenderRect
	{
	public: // Constructors/Destructor/Assignments
		RenderRect() = default;
		~RenderRect() = default;

		RenderRect(RenderRect const &) = delete;
		RenderRect(RenderRect &&) = default;

		RenderRect & operator=(RenderRect const &) = delete;
		RenderRect & operator=(RenderRect &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		constexpr SDL_Texture * getTexture() const { return m_texture ? m_texture->get() : nullptr; }
		constexpr std::optional<SDL_Rect> const & getSourceRect() const { return m_sourceRect; }
		constexpr math::Vector2d const & getPosition() const { return m_position; }
		constexpr double const & getRotation() const { return m_rotation; }
		constexpr math::Vector2d const & getOrigin() const { return m_origin; }
		constexpr math::Vector2d const & getSize() const { return m_size; }
		constexpr bool const & getFacing() const { return m_isRight; }

		RenderRect & setTexture(std::shared_ptr<app::gra::Texture> texture);
		RenderRect & setSourceRect(std::optional<SDL_Rect> const & sourceRect);
		RenderRect & setPosition(app::math::Vector2f const & position);
		RenderRect & setRotation(double const & rotation);
		RenderRect & setOrigin(app::math::Vector2d const & origin);
		RenderRect & setSize(app::math::Vector2d const & size);
		RenderRect & setFacing(bool isRight);
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
		std::shared_ptr<app::gra::Texture> m_texture;
		std::optional<SDL_Rect> m_sourceRect;
		math::Vector2d m_position;
		math::Vector2d m_origin;
		math::Vector2d m_size;
		double m_rotation;
		bool m_isRight;
	};
}

#endif // !_GRAPHICS_RENDER_RECT_H
