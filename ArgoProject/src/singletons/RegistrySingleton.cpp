﻿#include "stdafx.h"
#include "RegistrySingleton.h"

/// 
/// @brief The only pointer to our registry instance.
/// 
/// <summary>
/// Keeps ownership of our registry instance so that any deletion is done automatically
/// via the unique pointers destructor.
/// </summary>
std::unique_ptr<app::Registry> app::sin::Registry::s_registry = nullptr;

/// 
/// @brief Retrieve a reference to our singleton registry.
/// 
/// <summary>
/// Checks if our instance app::sin::Reg::s_registry is instanciated, and instanciate it if it isn't,
/// effectevily lazy loading our registry and retrieve a reference to it.
/// </summary>
/// <returns>reference to our singleton registry instance.</returns>
app::Registry & app::sin::Registry::get()
{
	if (!s_registry) { s_registry = std::make_unique<app::Registry>(); }
	return *s_registry;
}

