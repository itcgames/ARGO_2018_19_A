#ifndef _GRAPHICS_AUDIO_MANAGER_H
#define _GRAPHICS_AUDIO_MANAGER_H

#include "graphics/AudioBufferMusic.h"
#include "graphics/AudioBufferSFX.h"

namespace app::gra
{
	class AudioManager
	{
	public: // Constructors/Destructor/Assignments
		AudioManager() = default;
		~AudioManager() = default;

		AudioManager(AudioManager const &) = delete;
		AudioManager(AudioManager &&) = default;

		AudioManager & operator=(AudioManager const &) = delete;
		AudioManager & operator=(AudioManager &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		
		//getters
		constexpr Mix_Music * getMusicAudio() const { return m_musicAudio ? m_musicAudio->get() : nullptr; }
		constexpr Mix_Chunk * getSFXAudio() const { return m_sfxAudio ? m_sfxAudio->get() : nullptr; }
		//setters
		void setAudioBuffer(std::shared_ptr<app::gra::AudioBufferMusic> audioBuffer);
		void setAudioBuffer(std::shared_ptr<app::gra::AudioBufferSFX> audioBuffer);

		void play();
		void pause();
		void stop();
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
		std::shared_ptr<app::gra::AudioBufferMusic> m_musicAudio;
		std::shared_ptr<app::gra::AudioBufferSFX> m_sfxAudio;
		bool m_isMusic;
	};
}

#endif // !_GRAPHICS_AUDIO_MANAGER_H
