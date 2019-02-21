#ifndef _GRAPHICS_TEXTURE_H
#define _GRAPHICS_TEXTURE_H

#include "deleters/SdlDeleter.h"

namespace app::gra
{
	class Texture
	{
	public: // Constructors/Destructor/Assignments
		Texture() = default;
		Texture(app::del::UPtrRenderer const & renderer, std::string_view file);
		~Texture() = default;

		Texture(Texture const &) = delete;
		Texture(Texture &&) = default;

		Texture & operator=(Texture const &) = delete;
		Texture & operator=(Texture &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		bool load(app::del::UPtrRenderer const & renderer, std::string_view file);
		SDL_Texture * get() const { return m_texture.get(); }
	public: // Public Static Variables
		static std::mutex s_sdlMutex;
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
		static del::UPtrTexture loadTexture(app::del::UPtrRenderer const & renderer, std::string_view file);
		static del::UPtrSurface loadSurface(std::string_view file);
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
		app::del::UPtrTexture m_texture;
	};
}

#endif // !_GRAPHICS_TEXTURE_H
