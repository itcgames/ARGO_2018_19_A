#ifndef _GRAPHICS_AUDIOBUFFER_SFX_H
#define _GRAPHICS_AUDIOBUFFER_SFX_H

#include "deleters/SdlDeleter.h"

namespace app::gra
{
	class AudioBufferSFX
	{
	public: // Constructors/Destructor/Assignments
		AudioBufferSFX() = default;
		AudioBufferSFX(std::string const & file, bool isMusic);
		~AudioBufferSFX() = default;

		AudioBufferSFX(AudioBufferSFX const &) = delete;
		AudioBufferSFX(AudioBufferSFX &&) = default;

		AudioBufferSFX & operator=(AudioBufferSFX const &) = delete;
		AudioBufferSFX & operator=(AudioBufferSFX &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		bool load(std::string const & file);
		Mix_Chunk * get() const { return m_chunk.get(); }
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
		app::del::UPtrChunk loadSFX(std::string const & file);
	private: // Private Member Functions
	private: // Private Static Variables
		static std::mutex s_sdlMutex;
	private: // Private Member Variables
		del::UPtrChunk m_chunk;
	};
}

#endif // !_GRAPHICS_AUDIOBUFFER_SFX_H
