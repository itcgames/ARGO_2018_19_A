#ifndef _COMP_AUDIO_H
#define _COMP_AUDIO_H

#include <SDL/SDL_audio.h>
#include <map>
#include <string>
#include "graphics/AudioBufferMusic.h"
#include "graphics/AudioBufferSFX.h"

namespace app::comp
{
	struct Audio
	{
	public: // Constructors/Destructor/Assignments
		Audio() = default;
		~Audio() = default;

		Audio(Audio const &) = default;
		Audio & operator=(Audio const &) = default;

		Audio(Audio &&) = default;
		Audio & operator=(Audio &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		struct Sound
		{
			Sound() {};
			Sound(std::string n, std::shared_ptr<app::gra::AudioBufferSFX> a);
			Sound(std::string n, std::shared_ptr<app::gra::AudioBufferMusic> a);
			bool m_isMusic;
			std::string m_name;
			std::shared_ptr<app::gra::AudioBufferSFX> m_audioSound = nullptr;
			std::shared_ptr<app::gra::AudioBufferMusic> m_audioMusic = nullptr;
		};
		//audio functions 
		void playAudio(std::string s, int loops);
		void pauseAudio(std::string s);
		void stopAudio(std::string s);
		//add sounds
		void addSFX(std::string s, std::shared_ptr<app::gra::AudioBufferSFX> audioSFX);
		void addMusic(std::string s, std::shared_ptr<app::gra::AudioBufferMusic> audioMusic);
	public: // Public Static Variables
	public: // Public Member Variables
		std::map<std::string, Sound> m_audioMap;
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions

	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_COMP_AIR_MOTION_H
