#include "stdafx.h"
#include "Font.h"
#include "singletons/WindowSingleton.h"

std::mutex app::gra::Font::s_sdlMutex = std::mutex();

app::gra::Font::Font(std::string const & file)
	: m_font(nullptr)
	, m_charSize(s_DEFAULT_CHAR_SIZE)
{
	this->load(file);
}

app::gra::Font::~Font()
{
	if (m_texture) { m_texture.reset(); }
}

bool app::gra::Font::load(std::string const & file)
{
	try
	{
		auto font = loadFont(file, m_charSize);
		if (font == nullptr) { throw std::exception(TTF_GetError()); }
		m_font.swap(font);

		return true;
	}
	catch (std::exception const & e)
	{
		Console::writeLine({ "ERROR: Failed to load font \"", file.data(), "\" [", e.what(), "]" });
		return false;
	}
}

bool app::gra::Font::prepare(app::gra::Font::Quality const & quality, std::string const & text, SDL_Color const & color)
{
	try
	{
		auto texture = renderFont(m_font, quality, text, color);
		if (texture == nullptr) { throw std::exception(); }
		m_texture.swap(texture);

		return true;
	}
	catch (std::exception const & e)
	{
		Console::writeLine({ "ERROR: Failed to prepare font [", e.what(), "]" });
		return false;
	}
}

app::del::UPtrFont app::gra::Font::loadFont(std::string const & file, std::int32_t const & charSize)
{
	// lock SDL access since it is not thread safe operation
	auto lock = std::lock_guard<decltype(s_sdlMutex)>(s_sdlMutex);
	TTF_Font * font = nullptr;
	font = TTF_OpenFont(file.c_str(), charSize);

	if (font == nullptr) { return nullptr; }

	return del::UPtrFont(font);
}

app::del::UPtrTexture app::gra::Font::renderFont(app::del::UPtrFont const & font, app::gra::Font::Quality const & quality, std::string const & text, SDL_Color const & color)
{
	auto lock = std::lock_guard<decltype(s_sdlMutex)>(s_sdlMutex);
	if (!font) { throw std::exception("ERROR: Font not loaded"); }
	SDL_Texture * pTexture = nullptr;
	auto surface = renderSurface(font, quality, text, color);

	pTexture = SDL_CreateTextureFromSurface(app::sin::Window::get().getRenderer().get(), surface.get());
	if (pTexture == nullptr) { throw std::exception((std::stringstream() << "ERROR: in \"RenderText::preRender\" [" << SDL_GetError() << "]").str().c_str()); }

	return del::UPtrTexture(pTexture);
}

app::del::UPtrSurface app::gra::Font::renderSurface(app::del::UPtrFont const & font, app::gra::Font::Quality const & quality, std::string const & text, SDL_Color const & color)
{
	SDL_Surface * pSurface = nullptr;

	pSurface = (quality == Quality::Blended)
		? TTF_RenderText_Blended(font.get(), text.c_str(), color)
		: TTF_RenderText_Solid(font.get(), text.c_str(), color);
	if (pSurface == nullptr) { throw std::exception((std::stringstream() << "ERROR: in \"RenderText::preSurface\" [" << TTF_GetError() << "]").str().c_str()); }

	return del::UPtrSurface(pSurface);
}
