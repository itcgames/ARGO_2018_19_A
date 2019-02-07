#include "stdafx.h"
#include "WindowSingleton.h"
#include "ControllerHandlerSingleton.h"
#include "KeyHandlerSingleton.h"
#include "MouseHandlerSingleton.h"

std::unique_ptr<app::gra::Window> app::sin::Window::s_window = nullptr;

app::gra::Window & app::sin::Window::get()
{
	if (!s_window)
	{
		s_window = std::make_unique<app::gra::Window>(
			sin::KeyHandler::get()
			, sin::MouseHandler::get()
			, sin::ControllerHandler::get()
			, gra::WindowParameters{ "ARGO Souls", 1366u, 768u });
	}
	return *s_window;
}
