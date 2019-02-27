#include "stdafx.h"
#include "AudioPlayer.h"
#include "singletons/ResourceManagerSingleton.h"

app::gra::AudioPlayer::AudioPlayer()
	: m_resourceManager(app::sin::ResourceManager::get())
{
}

/// <summary>
/// </summary>
/// <param name="key">identifies what audio to play</param>
/// <param name="loops">tells the mixer class how many times to loop the audio. if -1 loop forever</param>
void app::gra::AudioPlayer::playAudioMusic(app::res::AudioKey const & key, int loops)
{
	if (Mix_PlayingMusic())
	{
		Mix_HaltMusic();
		Mix_PlayMusic(m_resourceManager.getAudioM(key)->get(), loops);
	}
	else if (Mix_PausedMusic())
	{
		Mix_ResumeMusic();
	}
	else
	{
		Mix_PlayMusic(m_resourceManager.getAudioM(key)->get(), loops);
	}
}

void app::gra::AudioPlayer::playAudioSFX(app::res::AudioKey const & key, int loops)
{
	Mix_PlayChannel(-1, m_resourceManager.getAudioS(key)->get(), loops);
}

void app::gra::AudioPlayer::pauseAudioMusic(app::res::AudioKey const & key)
{
	Mix_PauseMusic();
}

void app::gra::AudioPlayer::pauseAudioSFX(app::res::AudioKey const & key)
{
	throw std::exception("Pausing sound effects not implemented");
}

void app::gra::AudioPlayer::stopAudioMusic(app::res::AudioKey const & key)
{
	Mix_HaltMusic();
}

void app::gra::AudioPlayer::stopAudioSFX(app::res::AudioKey const & key)
{
	throw std::exception("Pausing sound effects not implemented");
}
