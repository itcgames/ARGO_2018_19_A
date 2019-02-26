#include "stdafx.h"
#include "ButtonSystem.h"
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
	using WidgetState = comp::Widget::State;
	m_registry.view<comp::Widget, comp::Presseable>()
		.each([&, this](app::Entity const entity, comp::Widget & widget, comp::Presseable & presseable)
	{
		if (widget.state != WidgetState::Highlighted && widget.state != WidgetState::Pressed) { return; }
		if (presseable.keyCommands.has_value())
		{
			for (auto const &[key, command] : presseable.keyCommands.value())
			{
				if (widget.state == WidgetState::Highlighted && m_keyHandler.isKeyPressed(key))
				{
					widget.state = WidgetState::Pressed;
					command->execute();
					return;
				}
				else if (widget.state == WidgetState::Pressed && m_keyHandler.isKeyUnpressed(key))
				{
					widget.state = WidgetState::Highlighted;
					return;
				}
			}
		}
		if (presseable.mouseCommands.has_value())
		{
			for (auto const &[key, command] : presseable.mouseCommands.value())
			{
				if (widget.state == WidgetState::Highlighted && m_mouseHandler.isButtonPressed(key))
				{
					widget.state = WidgetState::Pressed;
					command->execute();
					return;
				}
				else if (widget.state == WidgetState::Pressed && m_mouseHandler.isButtonUnpressed(key))
				{
					widget.state = WidgetState::Highlighted;
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
					if (widget.state == WidgetState::Highlighted && m_controllerHandler.isButtonPressed(i, key))
					{
						widget.state = WidgetState::Pressed;
						command->execute();
						return;
					}
					else if (widget.state == WidgetState::Pressed && m_controllerHandler.isButtonUnpressed(i, key))
					{
						widget.state = WidgetState::Highlighted;
						return;
					}
				}
			}
		}
	});
}
