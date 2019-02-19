#include "stdafx.h"
#include "AudioSystem.h"

// components
#include "components/Audio.h"
#include "components/Dimensions.h"
#include "components/Render.h"
#include "components/Camera.h"

app::sys::AudioSystem::AudioSystem()
	: BaseSystem()
{
}

void app::sys::AudioSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Audio>()
		.each([&, this](app::Entity const entity, comp::Audio & audio)
	{
		m_audioManager.setAudioBuffer(audio.audio);
		m_audioManager.play();
	});
}
