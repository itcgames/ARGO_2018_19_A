#ifndef _GRAPHICS_AUDIO_PLAYER_H
#define _GRAPHICS_AUDIO_PLAYER_H

#include "resources/AudioKey.h"
#include "resources/ResourceManager.h"

namespace app::gra
{
	class AudioPlayer
	{
	public: // Constructors/Destructor/Assignments
		AudioPlayer();
		~AudioPlayer() = default;

		AudioPlayer(AudioPlayer const &) = default;
		AudioPlayer & operator=(AudioPlayer const &) = default;

		AudioPlayer(AudioPlayer &&) = default;
		AudioPlayer & operator=(AudioPlayer &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		void playAudioMusic(app::res::AudioKey const & key, int loops = 0);
		void playAudioSFX(app::res::AudioKey const & key, int loops = 0);

		void pauseAudioMusic(app::res::AudioKey const & key);
		void pauseAudioSFX(app::res::AudioKey const & key);
		
		void stopAudioMusic(app::res::AudioKey const & key);
		void stopAudioSFX(app::res::AudioKey const & key);
	public: // Public Static Variables
		constexpr static int s_LOOP_FOREVER = -1;
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
		app::res::ResourceManager<true> & m_resourceManager;
	};
}

#endif // !_GRAPHICS_AUDIO_PLAYER_H
