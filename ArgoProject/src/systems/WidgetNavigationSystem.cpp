﻿#include "stdafx.h"
#include "WidgetNavigationSystem.h"
#include "singletons/KeyHandlerSingleton.h"
#include "singletons/ResourceManagerSingleton.h"

// components
#include "components/Widget.h"
#include "components/Render.h"

app::sys::WidgetNavigationSystem::WidgetNavigationSystem()
	: BaseSystem()
	, m_keyHandler(app::sin::KeyHandler::get())
	, m_resourceManager(app::sin::ResourceManager::get())
{
}

void app::sys::WidgetNavigationSystem::update(app::time::seconds const & dt)
{
	auto buttonPressed = false;
	auto renderView = m_registry.view<comp::Widget, comp::Render>();
	auto widgetView = m_registry.view<comp::Widget>();
	widgetView.each([&, this](app::Entity const entity, comp::Widget & widget)
	{
		if (widget.state != comp::Widget::State::Highlighted || buttonPressed) { return; }
		widget.prevState = widget.state;
		if (widget.prevState == comp::Widget::State::Active) { return; }
		if (widget.left.has_value() && m_keyHandler.isKeyPressed({ SDLK_a, SDLK_LEFT }))
		{
			assert(widgetView.contains(widget.left.value()));
			buttonPressed = true;
			widget.prevState = comp::Widget::State::Highlighted;
			if (renderView.contains(widget.left.value()))
			{
				auto & render = renderView.get<comp::Render>(widget.left.value());
				render.texture = m_resourceManager.getTexture(app::res::TextureKey::DebugRed);
			}
			widget.state = comp::Widget::State::Active;
			if (renderView.contains(entity))
			{
				auto & render = renderView.get<comp::Render>(entity);
				render.texture = m_resourceManager.getTexture(app::res::TextureKey::Debug);
			}

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
			buttonPressed = true;
			widget.prevState = comp::Widget::State::Highlighted;
			if (renderView.contains(widget.right.value()))
			{
				auto & render = renderView.get<comp::Render>(widget.right.value());
				render.texture = m_resourceManager.getTexture(app::res::TextureKey::DebugRed);
			}
			widget.state = comp::Widget::State::Active;
			if (renderView.contains(entity))
			{
				auto & render = renderView.get<comp::Render>(entity);
				render.texture = m_resourceManager.getTexture(app::res::TextureKey::Debug);
			}
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
			buttonPressed = true;
			widget.prevState = comp::Widget::State::Highlighted;
			if (renderView.contains(widget.up.value()))
			{
				auto & render = renderView.get<comp::Render>(widget.up.value());
				render.texture = m_resourceManager.getTexture(app::res::TextureKey::DebugRed);
			}
			widget.state = comp::Widget::State::Active;
			if (renderView.contains(entity))
			{
				auto & render = renderView.get<comp::Render>(entity);
				render.texture = m_resourceManager.getTexture(app::res::TextureKey::Debug);
			}
			auto & upWidget = widgetView.get(widget.up.value());
			upWidget.prevState = comp::Widget::State::Active;
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
			buttonPressed = true;
			widget.prevState = comp::Widget::State::Highlighted;
			if (renderView.contains(widget.down.value()))
			{
				auto & render = renderView.get<comp::Render>(widget.down.value());
				render.texture = m_resourceManager.getTexture(app::res::TextureKey::DebugRed);
			}
			widget.state = comp::Widget::State::Active;
			if (renderView.contains(entity))
			{
				auto & render = renderView.get<comp::Render>(entity);
				render.texture = m_resourceManager.getTexture(app::res::TextureKey::Debug);
			}
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
