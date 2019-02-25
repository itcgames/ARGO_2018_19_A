#ifndef _AUDIO_PLAYER_SINGLETON_H
#define _AUDIO_PLAYER_SINGLETON_H

#include "graphics/AudioPlayer.h"

namespace app::sin
{
	class AudioPlayer
	{
	private: // Constructors/Destructor/Assignments
		AudioPlayer() = default;
		~AudioPlayer() = default;

		AudioPlayer(AudioPlayer const &) = default;
		AudioPlayer & operator=(AudioPlayer const &) = default;

		AudioPlayer(AudioPlayer &&) = default;
		AudioPlayer & operator=(AudioPlayer &&) = default;

	public: // Public Static Functions
		static app::gra::AudioPlayer & get();
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
		static std::unique_ptr<app::gra::AudioPlayer> s_audioPlayer;
	private: // Private Member Variables
	};
}

#endif // !_AUDIO_PLAYER_SINGLETON_H
