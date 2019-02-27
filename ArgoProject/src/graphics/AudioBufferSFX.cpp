#include "stdafx.h"
#include "AudioBufferSFX.h"

std::mutex app::gra::AudioBufferSFX::s_sdlMutex = std::mutex();

app::gra::AudioBufferSFX::AudioBufferSFX(std::string const & file, bool isMusic)
	: m_chunk(nullptr)
{
	this->load(file);
}

bool app::gra::AudioBufferSFX::load(std::string const & file)
{
	try
	{
		auto chunk = loadSFX(file);
		if (chunk == nullptr) { throw std::exception(SDL_GetError()); }
		m_chunk.swap(chunk);
		return true;
	}
	catch (std::exception const & e)
	{
		Console::writeLine({ "ERROR: Failed to load sound \"", file.data(), "\" [", e.what(), "]" });
		return false;
	}
}

app::del::UPtrChunk app::gra::AudioBufferSFX::loadSFX(std::string const & file)
{
	// lock SDL access since it is not thread safe operation
	auto lock = std::lock_guard<decltype(s_sdlMutex)>(s_sdlMutex);
	Mix_Chunk * chunk = nullptr;
	chunk = Mix_LoadWAV(file.c_str());
	if (chunk == nullptr) { return nullptr; }

	return app::del::UPtrChunk (chunk);
}
