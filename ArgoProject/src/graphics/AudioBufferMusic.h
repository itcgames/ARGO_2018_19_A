#ifndef _GRAPHICS_AUDIOBUFFER_MUSIC_H
#define _GRAPHICS_AUDIOBUFFER_MUSIC_H

#include "deleters/SdlDeleter.h"

namespace app::gra
{
	class AudioBufferMusic
	{
	public: // Constructors/Destructor/Assignments
		AudioBufferMusic() = default;
		AudioBufferMusic(std::string const & file, bool isMusic);
		~AudioBufferMusic() = default;

		AudioBufferMusic(AudioBufferMusic const &) = delete;
		AudioBufferMusic(AudioBufferMusic &&) = default;

		AudioBufferMusic & operator=(AudioBufferMusic const &) = delete;
		AudioBufferMusic & operator=(AudioBufferMusic &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		bool load(std::string const & file);
		Mix_Music * get() const { return m_music.get(); }
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
		app::del::UPtrMusic loadMusic(std::string const & file);
	private: // Private Member Functions
	private: // Private Static Variables
		static std::mutex s_sdlMutex;
	private: // Private Member Variables
		del::UPtrMusic m_music;
	};
}

#endif // !_GRAPHICS_AUDIOBUFFER_MUSIC_H
