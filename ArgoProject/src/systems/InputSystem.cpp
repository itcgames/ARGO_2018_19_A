#include "stdafx.h"
#include "InputSystem.h"
#include "components/Input.h"
#include "components/Commandable.h"
#include "commands/JumpCommand.h"

app::sys::InputSystem::InputSystem(app::inp::KeyHandler& handler)
	: BaseSystem()
	, m_keyHandler(handler)
{
}

void app::sys::InputSystem::update(app::time::seconds const & dt)
{

	m_registry.view<comp::Input, comp::Commandable>()
		.each([&, this](app::Entity const entity, comp::Input & input, comp::Commandable& commandable) 
	{
		for (auto const &[key, command] : input.keyDownCommands)
		{
			if (m_keyHandler.isKeyDown(key)) 
			{ 
				if (key != SDLK_SPACE) 
				{
					commandable.list.push_front(command);
				}
			}
			if (m_keyHandler.isKeyPressed(key))
			{
				if (key == SDLK_SPACE)
				{
					commandable.list.push_front(command);
				}
			}
		}
	});

}
