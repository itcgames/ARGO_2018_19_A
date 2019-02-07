#include "stdafx.h"
#include "MouseHandlerSingleton.h"

std::unique_ptr<app::inp::MouseHandler> app::sin::MouseHandler::s_mouseHandler = nullptr;

app::inp::MouseHandler & app::sin::MouseHandler::get()
{
	if (!s_mouseHandler) { s_mouseHandler = std::make_unique<app::inp::MouseHandler>(); }
	return *s_mouseHandler;
}
