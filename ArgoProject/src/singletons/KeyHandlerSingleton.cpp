#include "stdafx.h"
#include "KeyHandlerSingleton.h"

std::unique_ptr<app::inp::KeyHandler> app::sin::KeyHandler::s_keyHandler = nullptr;

app::inp::KeyHandler & app::sin::KeyHandler::get()
{
	if (!s_keyHandler) { s_keyHandler = std::make_unique<app::inp::KeyHandler>(); }
	return *s_keyHandler;
}
