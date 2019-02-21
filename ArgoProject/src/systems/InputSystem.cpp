#include "stdafx.h"
#include "InputSystem.h"
#include "singletons/KeyHandlerSingleton.h"
#include "components/Audio.h"
#include "components/Input.h"
#include "components/Commandable.h"
#include "commands/JumpCommand.h"


app::sys::InputSystem::InputSystem()
	: BaseSystem()
	, m_keyHandler(app::sin::KeyHandler::get())
{
}

void app::sys::InputSystem::update(app::time::seconds const & dt)
{

	m_registry.view<comp::Input, comp::Commandable, comp::Audio>()
		.each([&, this](app::Entity const entity, comp::Input & input, comp::Commandable& commandable, comp::Audio & audio) 
	{
		for (auto const &[key, command] : input.keyDownCommands)
		{
			if (m_keyHandler.isKeyDown(key)) 
			{ 
				commandable.list.push_front(command);
			//	if(key == )
			}
		}
		for (auto const &[key, command] : input.keyPressedCommands)
		{
			if (m_keyHandler.isKeyPressed(key))
			{
				commandable.list.push_front(command);
				if (key == 32)
				{
					audio.playAudio("Jump", 0);
				}
			}
		}
	});

}
