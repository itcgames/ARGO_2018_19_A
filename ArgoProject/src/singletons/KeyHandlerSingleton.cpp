#include "stdafx.h"
#include "KeyHandlerSingleton.h"

app::inp::KeyHandler & app::sin::KeyHandler::get()
{
	if (!s_keyHandler) { s_keyHandler = std::make_unique<app::inp::KeyHandler>(); }
	return *s_keyHandler;
}
