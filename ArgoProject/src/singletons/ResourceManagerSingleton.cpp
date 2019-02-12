#include "stdafx.h"
#include "ResourceManagerSingleton.h"

std::unique_ptr<app::res::ResourceManager<true>> app::sin::ResourceManager::s_resourceManager = nullptr;

app::res::ResourceManager<true>& app::sin::ResourceManager::get()
{
	if (!s_resourceManager) { s_resourceManager = std::make_unique<app::res::ResourceManager<true>>(); }
	return *s_resourceManager;
}
