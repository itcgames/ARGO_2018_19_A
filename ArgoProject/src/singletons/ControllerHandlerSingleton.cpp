#include "stdafx.h"
#include "ControllerHandlerSingleton.h"

std::unique_ptr<app::inp::ControllerHandler> app::sin::ControllerHandler::s_controllerHandler = nullptr;

app::inp::ControllerHandler & app::sin::ControllerHandler::get()
{
	if (!s_controllerHandler) { s_controllerHandler = std::make_unique<app::inp::ControllerHandler>(); }
	return *s_controllerHandler;
}
