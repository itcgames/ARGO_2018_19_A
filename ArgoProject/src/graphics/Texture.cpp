#include "stdafx.h"
#include "Texture.h"

std::mutex app::gra::Texture::s_sdlMutex = std::mutex();

app::gra::Texture::Texture(app::del::UPtrRenderer const & renderer, std::string_view file)
	: m_texture(nullptr)
{
	this->load(renderer, file);
}

bool app::gra::Texture::load(app::del::UPtrRenderer const & renderer, std::string_view file)
{
	try
	{
		auto texture = loadTexture(renderer, file);
		if (texture == nullptr) { throw std::exception(SDL_GetError()); }
		m_texture.swap(texture);

		return true;
	}
	catch (std::exception const & e)
	{
		Console::writeLine({ "ERROR: Failed to load image \"", file.data(), "\" [", e.what(), "]" });
		return false;
	}
}

app::del::UPtrTexture app::gra::Texture::loadTexture(app::del::UPtrRenderer const & renderer, std::string_view file)
{
	auto surface = Texture::loadSurface(file);
	SDL_Texture * texture = nullptr;
	{
		// lock SDL access since it is not thread safe operation
		auto lock = std::lock_guard<decltype(s_sdlMutex)>(s_sdlMutex);
		texture = SDL_CreateTextureFromSurface(renderer.get(), surface.get());
	}
	if (texture == nullptr) { return nullptr; }

	return app::del::UPtrTexture(texture);
}

app::del::UPtrSurface app::gra::Texture::loadSurface(std::string_view file)
{
	SDL_Surface * surface = nullptr;
	{
		// lock SDL access since it is not thread safe operation
		auto lock = std::lock_guard<decltype(s_sdlMutex)>(s_sdlMutex);
		surface = IMG_Load(file.data());
	}
	if (surface == nullptr) { return nullptr; }

	return app::del::UPtrSurface(surface);
}
