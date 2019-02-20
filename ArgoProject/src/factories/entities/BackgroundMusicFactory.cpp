#include "stdafx.h"
#include "BackgroundMusicFactory.h"
#include "components/Audio.h"

app::fact::BackgroundMusicFactory::BackgroundMusicFactory(
	std::string s
	,app::res::AudioKey const & audioKey
)
	: EntityFactory()
	, m_name(s)
	, m_audioKey(audioKey)
{
}

app::Entity const app::fact::BackgroundMusicFactory::create()
{
	app::Entity const entity = m_registry.create();

	auto audio = comp::Audio();
	audio.addMusic(m_name, m_resourceManager.getAudioM(m_audioKey));
	m_registry.assign<decltype(audio)>(entity, std::move(audio));

	return entity;
}
