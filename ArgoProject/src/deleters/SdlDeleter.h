﻿#ifndef _SDL_DELETER_H
#define _SDL_DELETER_H

namespace app::del
{
	class SdlDeleter
	{
	public: // Constructors/Destructor/Assignments
		SdlDeleter() = default;
		SdlDeleter(SdlDeleter const &) = default;
		SdlDeleter(SdlDeleter &&) = default;

		~SdlDeleter() = default;

		SdlDeleter & operator=(SdlDeleter const &) = default;
		SdlDeleter & operator=(SdlDeleter &&) = default;
	public: // Public Static Functions
	public: // Public Member Functions
		void operator()(SDL_Window * pWindow) const;
		void operator()(SDL_Renderer * pRenderer) const;
		void operator()(SDL_Texture * pTexture) const;
		void operator()(SDL_Surface * pSurface) const;
		void operator()(SDL_GameController * pGameController) const;
		void operator()(SDL_Haptic * pHaptic) const;
		void operator()(Mix_Music * pMusic) const;
		void operator()(Mix_Chunk * pChunk) const;
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
	};

	// Unique Pointers
	typedef std::unique_ptr<SDL_Renderer, SdlDeleter> UPtrRenderer;
	typedef std::unique_ptr<SDL_Window, SdlDeleter> UPtrWindow;
	typedef std::unique_ptr<SDL_Texture, SdlDeleter> UPtrTexture;
	typedef std::unique_ptr<SDL_Surface, SdlDeleter> UPtrSurface;
	typedef std::unique_ptr<SDL_GameController, SdlDeleter> UPtrGameController;
	typedef std::unique_ptr<SDL_Haptic, SdlDeleter> UPtrHaptic;
	typedef std::unique_ptr<Mix_Music, SdlDeleter> UPtrMusic;
	typedef std::unique_ptr<Mix_Chunk, SdlDeleter> UPtrChunk;
}

#endif // !_SDL_DELETER_H
