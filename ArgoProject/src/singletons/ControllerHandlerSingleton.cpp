#include "stdafx.h"
#include "ControllerHandlerSingleton.h"

app::inp::ControllerHandler & app::sin::ControllerHandler::get()
{
	if (!s_controllerHandler) { s_controllerHandler = std::make_unique<app::inp::ControllerHandler>(); }
	return *s_controllerHandler;
}
