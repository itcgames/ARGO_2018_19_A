#include "stdafx.h"
#include "ButtonSystem.h"
#include "utilities/variant.h"
#include "singletons/KeyHandlerSingleton.h"
#include "singletons/MouseHandlerSingleton.h"
#include "singletons/ControllerHandlerSingleton.h"

// components
#include "components/Widget.h"
#include "components/Presseable.h"

app::sys::ButtonSystem::ButtonSystem()
	: BaseSystem()
	, m_keyHandler(app::sin::KeyHandler::get())
	, m_mouseHandler(app::sin::MouseHandler::get())
	, m_controllerHandler(app::sin::ControllerHandler::get())
{
}

void app::sys::ButtonSystem::update(app::time::seconds const & dt)
{
	m_registry.view<comp::Widget, comp::Presseable>()
		.each([&, this](app::Entity const entity, comp::Widget const & widget, comp::Presseable & presseable)
	{
		if (widget.state != comp::Widget::State::Highlighted) { return; }
		if (presseable.keyCommands.has_value())
		{
			for (auto const &[key, command] : presseable.keyCommands.value())
			{
				if (m_keyHandler.isKeyPressed(key))
				{
					command->execute();
					return;
				}
			}
		}
		if (presseable.mouseCommands.has_value())
		{
			for (auto const &[key, command] : presseable.mouseCommands.value())
			{
				if (m_mouseHandler.isButtonPressed(key))
				{
					command->execute();
					return;
				}
			}
		}

		if (presseable.buttonCommands.has_value())
		{
			constexpr auto MAX_CONTROLLERS = 8;
			for (app::inp::ControllerIndex i = 0; i < MAX_CONTROLLERS; ++i)
			{
				for (auto const &[key, command] : presseable.buttonCommands.value())
				{
					if (m_controllerHandler.isButtonPressed(i, key))
					{
						command->execute();
						return;
					}
				}
			}
		}
	});
}
