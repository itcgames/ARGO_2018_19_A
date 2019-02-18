#ifndef _GRAPHICS_AUDIOBUFFER_H
#define _GRAPHICS_AUDIOBUFFER_H

#include "deleters/SdlDeleter.h"

namespace app::gra
{
	class AudioBuffer
	{
	public: // Constructors/Destructor/Assignments
		AudioBuffer() = default;
		AudioBuffer(std::string const & file, bool isMusic);
		~AudioBuffer() = default;

		AudioBuffer(AudioBuffer const &) = delete;
		AudioBuffer(AudioBuffer &&) = default;

		AudioBuffer & operator=(AudioBuffer const &) = delete;
		AudioBuffer & operator=(AudioBuffer &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		bool load(std::string const & file);
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
		app::del::UPtrMusic loadMusic(std::string const & file);
		app::del::UPtrChunk loadSFX(std::string const & file);
	private: // Private Member Functions
	private: // Private Static Variables
		static std::mutex s_sdlMutex;
	private: // Private Member Variables
		del::UPtrMusic m_music;
		del::UPtrChunk m_sfx;
	};
}

#endif // !_GRAPHICS_AUDIOBUFFER_H
