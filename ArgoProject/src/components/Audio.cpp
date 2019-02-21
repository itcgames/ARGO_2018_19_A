#include "stdafx.h"
#include "Audio.h"

app::comp::Audio::Sound::Sound(std::string n, std::shared_ptr<app::gra::AudioBufferSFX> a)
{
	m_isMusic = false;
	m_audioSound = a;
	m_name = n;
}

app::comp::Audio::Sound::Sound(std::string n, std::shared_ptr<app::gra::AudioBufferMusic> a)
{
	m_isMusic = true;
	m_audioMusic = a;
	m_name = n;
}

void app::comp::Audio::addMusic(std::string s, std::shared_ptr<app::gra::AudioBufferMusic> audioMusic)
{
	m_audioMap[s] =  Sound(s, audioMusic);
}

void app::comp::Audio::addSFX(std::string s, std::shared_ptr<app::gra::AudioBufferSFX> audioSFX)
{
	m_audioMap[s] = Sound(s, audioSFX);
}

void app::comp::Audio::playAudio(std::string s, int loops)
{
	if (m_audioMap.empty())
	{
		return;
	}
	else
	{
		if (m_audioMap[s].m_isMusic)
		{
			if (!Mix_PlayingMusic())
			{
				Mix_PlayMusic(m_audioMap[s].m_audioMusic->get(), loops);
			}
			else if (Mix_PausedMusic())
			{
				Mix_ResumeMusic();
			}
		}
		else
		{
			Mix_PlayChannel(-1,m_audioMap[s].m_audioSound->get(), loops);
		}
	}
} 

void::app::comp::Audio::pauseAudio(std::string s)
{
	if (m_audioMap.empty())
	{
		return;
	}
	else
	{
		if (m_audioMap[s].m_isMusic)
		{
			Mix_PauseMusic();
		}
	}
}

void::app::comp::Audio::stopAudio(std::string s)
{
	if (m_audioMap.empty())
	{
		return;
	}
	else
	{
		if (m_audioMap[s].m_isMusic)
		{
			Mix_HaltMusic();
		}
	}
}