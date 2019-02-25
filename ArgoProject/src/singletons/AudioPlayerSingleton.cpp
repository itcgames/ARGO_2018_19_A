#include "stdafx.h"
#include "AudioPlayerSingleton.h"

std::unique_ptr<app::gra::AudioPlayer> app::sin::AudioPlayer::s_audioPlayer = nullptr;

app::gra::AudioPlayer & app::sin::AudioPlayer::get()
{
	if (!s_audioPlayer) { s_audioPlayer = std::make_unique<app::gra::AudioPlayer>(); }
	return *s_audioPlayer;
}
