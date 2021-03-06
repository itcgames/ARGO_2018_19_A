#include "stdafx.h"
#include "AudioBufferMusic.h"

std::mutex app::gra::AudioBufferMusic::s_sdlMutex = std::mutex();

app::gra::AudioBufferMusic::AudioBufferMusic(std::string const & file, bool isMusic)
	: m_music(nullptr)
{
	this->load(file);
}

bool app::gra::AudioBufferMusic::load(std::string const & file)
{
	try
	{
		auto music = loadMusic(file);
		if (music == nullptr) { throw std::exception(SDL_GetError()); }
		m_music.swap(music);
		return true;
	}
	catch (std::exception const & e)
	{
		Console::writeLine({ "ERROR: Failed to load sound \"", file.data(), "\" [", e.what(), "]" });
		return false;
	}
}

app::del::UPtrMusic app::gra::AudioBufferMusic::loadMusic(std::string const & file)
{
	// lock SDL access since it is not thread safe operation
	auto lock = std::lock_guard<decltype(s_sdlMutex)>(s_sdlMutex);
	Mix_Music * music = nullptr;
	music = Mix_LoadMUS(file.c_str());
	if (music == nullptr) { return nullptr; }

	return app::del::UPtrMusic(music);
}
