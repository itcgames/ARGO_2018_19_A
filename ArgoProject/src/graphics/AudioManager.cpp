#include "stdafx.h"
#include "AudioManager.h"

void app::gra::AudioManager::setAudioBuffer(std::shared_ptr<app::gra::AudioBufferMusic> audioBuffer)
{
	m_musicAudio = audioBuffer;
	m_sfxAudio.reset();
}

void app::gra::AudioManager::setAudioBuffer(std::shared_ptr<app::gra::AudioBufferSFX> audioBuffer)
{
	m_sfxAudio = audioBuffer; 
	m_musicAudio.reset();
}

void app::gra::AudioManager::play()
{
	if (m_isMusic)
	{
		if (!Mix_PlayingMusic())
		{
			Mix_PlayMusic(m_musicAudio->get(),-1);
		}
	}
}

void app::gra::AudioManager::pause()
{

}

void app::gra::AudioManager::stop()
{

}