#ifndef _GRAPHICS_FONT_H
#define _GRAPHICS_FONT_H

#include "deleters/SdlTtfDeleter.h"

namespace app::gra
{
	class Font
	{
	public: // Public typedefs/enums/usings
		enum class Quality
		{
			Solid, Blended
		};
	public: // Constructors/Destructor/Assignments
		Font() = default;
		Font(std::string const & file);
		~Font();

		Font(Font const &) = default;
		Font & operator=(Font const &) = default;

		Font(Font &&) = default;
		Font & operator=(Font &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		bool load(std::string const & file);
		bool prepare(app::gra::Font::Quality const & quality, std::string const & text, SDL_Color const & color);
		TTF_Font * get() const { return m_font.get(); }
		SDL_Texture * getTexture() const { return m_texture.get(); }
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
		static del::UPtrFont loadFont(std::string const & file, std::int32_t const & charSize);
		static del::UPtrTexture renderFont(app::del::UPtrFont const & font, app::gra::Font::Quality const & quality, std::string const & text, SDL_Color const & color);
		static del::UPtrSurface renderSurface(app::del::UPtrFont const & font, app::gra::Font::Quality const & quality, std::string const & text, SDL_Color const & color);
	private: // Private Member Functions
	private: // Private Static Variables
		static std::mutex s_sdlMutex;
		constexpr static std::int32_t s_defaultCharSize = 128;
	private: // Private Member Variables
		del::UPtrFont m_font;
		del::UPtrTexture m_texture;
		std::int32_t m_charSize = s_defaultCharSize;
	};
}

#endif // !_GRAPHICS_FONT_H
