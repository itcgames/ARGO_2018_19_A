#include "stdafx.h"
#include "WidgetNavigationSystem.h"
#include "singletons/KeyHandlerSingleton.h"

// components
#include "components/Widget.h"

app::sys::WidgetNavigationSystem::WidgetNavigationSystem()
	: BaseSystem()
	, m_keyHandler(app::sin::KeyHandler::get())
{
}

void app::sys::WidgetNavigationSystem::update(app::time::seconds const & dt)
{
	auto widgetView = m_registry.view<comp::Widget>();
	widgetView.each([&, this](app::Entity const entity, comp::Widget & widget)
	{
		if (widget.state != comp::Widget::State::Highlighted) { return; }
		if (widget.left.has_value() && m_keyHandler.isKeyPressed({ SDLK_a, SDLK_LEFT }))
		{
			assert(widgetView.contains(widget.left.value()));
			widget.state = comp::Widget::State::Active;
			auto & leftWidget = widgetView.get(widget.left.value());
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
			widget.state = comp::Widget::State::Active;
			auto & rightWidget = widgetView.get(widget.right.value());
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
			widget.state = comp::Widget::State::Active;
			auto & upWidget = widgetView.get(widget.up.value());
			upWidget.state = comp::Widget::State::Highlighted;
			if constexpr (s_DEBUG_MODE)
			{
				app::Console::writeLine({ "Moved up from entity[", std::to_string(entity), "] to entity[", std::to_string(widget.up.value()), "]" });
			}
			return;
		}
		if (widget.down.has_value() && m_keyHandler.isKeyPressed({ SDLK_s, SDLK_DOWN }))
		{
			assert(widgetView.contains(widget.down.value()));
			widget.state = comp::Widget::State::Active;
			auto & downWidget = widgetView.get(widget.down.value());
			downWidget.state = comp::Widget::State::Highlighted;
			if constexpr (s_DEBUG_MODE)
			{
				app::Console::writeLine({ "Moved down from entity[", std::to_string(entity), "] to entity[", std::to_string(widget.down.value()), "]" });
			}
			return;
		}
	});
}
