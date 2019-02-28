#include "stdafx.h"
#include "WidgetNavigationSystem.h"
#include "singletons/KeyHandlerSingleton.h"
#include "singletons/ControllerHandlerSingleton.h"

// components
#include "components/Widget.h"

app::sys::WidgetNavigationSystem::WidgetNavigationSystem()
	: BaseSystem()
	, m_keyHandler(app::sin::KeyHandler::get())
	, m_controllerHandler(app::sin::ControllerHandler::get())
{
}

void app::sys::WidgetNavigationSystem::update(app::time::seconds const & dt)
{
	using Axis = app::inp::ControllerAxisCode;
	auto widgetView = m_registry.view<comp::Widget>();
	auto const & LEFT_PRESSED =
		m_keyHandler.isKeyPressed({ SDLK_a, SDLK_LEFT })
		|| this->isAxisOver({ Axis::SDL_CONTROLLER_AXIS_LEFTX }, s_THRESHOLD);
	auto const & DOWN_PRESSED =
		m_keyHandler.isKeyPressed({ SDLK_s, SDLK_DOWN })
		|| this->isAxisOver({ Axis::SDL_CONTROLLER_AXIS_LEFTY }, s_THRESHOLD);

	widgetView.each([&, this](app::Entity const entity, comp::Widget & widget)
	{
		if (widget.state != comp::Widget::State::Highlighted) { return; }
		if (widget.prevState == comp::Widget::State::Active)
		{
			widget.prevState = widget.state;
			return;
		}
		if (widget.left.has_value() && LEFT_PRESSED)
		{
			assert(widgetView.contains(widget.left.value()));
			widget.prevState = comp::Widget::State::Highlighted;
			widget.state = comp::Widget::State::Active;
			auto & leftWidget = widgetView.get(widget.left.value());
			leftWidget.prevState = comp::Widget::State::Active;
			leftWidget.state = comp::Widget::State::Highlighted;
			if constexpr (s_DEBUG_MODE)
			{
				app::Console::writeLine({ "Moved left from entity[", std::to_string(entity), "] to entity[", std::to_string(widget.left.value()), "]" });
			}
			return;
		}
		if (widget.right.has_value() && m_keyHandler.isKeyPressed({ SDLK_d, SDLK_RIGHT }))
		{
			assert(widgetView.contains(widget.right.value()));
			widget.prevState = comp::Widget::State::Highlighted;
			widget.state = comp::Widget::State::Active;
			auto & rightWidget = widgetView.get(widget.right.value());
			rightWidget.prevState = comp::Widget::State::Active;
			rightWidget.state = comp::Widget::State::Highlighted;
			if constexpr (s_DEBUG_MODE)
			{
				app::Console::writeLine({ "Moved right from entity[", std::to_string(entity), "] to entity[", std::to_string(widget.right.value()), "]" });
			}
			return;
		}
		if (widget.up.has_value() && m_keyHandler.isKeyPressed({ SDLK_w, SDLK_UP }))
		{
			assert(widgetView.contains(widget.up.value()));
			widget.prevState = comp::Widget::State::Highlighted;
			widget.state = comp::Widget::State::Active;
			auto & upWidget = widgetView.get(widget.up.value());
			upWidget.prevState = comp::Widget::State::Active;
			upWidget.state = comp::Widget::State::Highlighted;
			if constexpr (s_DEBUG_MODE)
			{
				app::Console::writeLine({ "Moved up from entity[", std::to_string(entity), "] to entity[", std::to_string(widget.up.value()), "]" });
			}
			return;
		}
		if (widget.down.has_value() && DOWN_PRESSED)
		{
			assert(widgetView.contains(widget.down.value()));
			widget.prevState = comp::Widget::State::Highlighted;
			widget.state = comp::Widget::State::Active;
			auto & downWidget = widgetView.get(widget.down.value());
			downWidget.prevState = comp::Widget::State::Active;
			downWidget.state = comp::Widget::State::Highlighted;
			if constexpr (s_DEBUG_MODE)
			{
				app::Console::writeLine({ "Moved down from entity[", std::to_string(entity), "] to entity[", std::to_string(widget.down.value()), "]" });
			}
			return;
		}
	});
}

bool app::sys::WidgetNavigationSystem::isAxisOver(std::initializer_list<app::inp::ControllerAxisCode> const & axises, double const & threshold)
{
	constexpr auto MAX_CONTROLLERS = 8;
	for (auto i = 0; i < MAX_CONTROLLERS; ++i)
	{
		for (auto const & axis : axises)
		{
			auto const & controllerAxis = m_controllerHandler.getAxis(i, axis);
			if ((threshold < 0.0)
				? controllerAxis < threshold
				: controllerAxis > threshold)
			{
				return true;
			}
		}
	}
	return false;
}
