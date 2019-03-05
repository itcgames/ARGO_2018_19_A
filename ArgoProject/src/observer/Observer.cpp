#include "stdafx.h"
#include "Observer.h"
#include "singletons/ResourceManagerSingleton.h"

app::obs::AudioObserver::AudioObserver()
	: m_audioPlayer(app::sin::AudioPlayer::get())
{

}

void app::obs::AudioObserver::notify(std::string s, SubjectEvent event)
{
	if (s == "JUMP")
	{
		m_audioPlayer.playAudioSFX(app::res::AudioKey::PlayerJump);
	}
	if (s == "BGM")
	{
		m_audioPlayer.playAudioMusic(app::res::AudioKey::BackgroundMusicTitle, app::gra::AudioPlayer::s_LOOP_FOREVER);
	}
}
