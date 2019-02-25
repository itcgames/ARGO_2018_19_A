#include "stdafx.h"
#include "SceneFactory.h"
#include "singletons/AudioPlayerSingleton.h"

app::fact::sce::SceneFactory::SceneFactory()
	: EntitiesFactory()
	, m_audioPlayer(app::sin::AudioPlayer::get())
{
}
