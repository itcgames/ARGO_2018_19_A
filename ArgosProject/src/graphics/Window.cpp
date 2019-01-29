#include "stdafx.h"
#include "Window.h"

app::gra::Window::Window(
	app::inp::KeyHandler & keyHandler
	, app::inp::MouseHandler & mouseHandler
	, std::string const & title
	, std::size_t const & width
	, std::size_t const & height
)
	: m_keyhandler(keyHandler)
	, m_mousehandler(mouseHandler)
	, m_open(true)
	, m_title(title)
	, m_width(width)
	, m_height(height)
	, m_window(nullptr)
	, m_renderer(nullptr)
{
	m_open = this->init();
}

app::gra::Window::~Window()
{
}

void app::gra::Window::pollEvents()
{
	typedef SDL_EventType EventType;
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
		case EventType::SDL_QUIT:
			m_open = false;
			break;
		case EventType::SDL_MOUSEMOTION:
			m_mousehandler.updatePosition(sdlEvent.motion.x, sdlEvent.motion.y);
			break;
		case EventType::SDL_MOUSEBUTTONUP:
			m_mousehandler.updateButton(sdlEvent.button.button, false);
			break;
		case EventType::SDL_MOUSEBUTTONDOWN:
			m_mousehandler.updateButton(sdlEvent.button.button, true);
			break;
		case EventType::SDL_KEYUP:
			m_keyhandler.updateKey(sdlEvent.key.keysym.sym, false);
			break;
		case EventType::SDL_KEYDOWN:
			m_keyhandler.updateKey(sdlEvent.key.keysym.sym, true);
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) { m_open = false; }
			break;
		default:
			break;
		}
	}
}

void app::gra::Window::clear() const
{
	SDL_SetRenderDrawColor(m_renderer.get(), s_BG_COLOR.r, s_BG_COLOR.g, s_BG_COLOR.b, s_BG_COLOR.a);
	SDL_RenderClear(m_renderer.get());
}

void app::gra::Window::display() const
{
	SDL_RenderPresent(m_renderer.get());
}

bool app::gra::Window::init()
{
	try
	{
		if (SDL_Init(SDL_INIT_VIDEO) != NULL)
		{
			Console::writeLine("ERROR: Failed to initialize SDL Video subsystem");
			return false;
		}
		if (!this->initWindow())
		{
			Console::writeLine({ "ERROR: Failed to initialize SDL Window::\"", m_title, "\"\n  ", SDL_GetError() });
			return false;
		}
		if (!this->initRenderer(m_window))
		{
			Console::writeLine({ "ERROR: Failed to initialize SDL Renderer from the SDL Window::\"", m_title, "\"\n  ", SDL_GetError() });
			return false;
		}

		return true;
	}
	catch (const std::exception& e)
	{
		Console::writeLine({ "ERROR: Exception has occurred [", e.what(), "]" });
		return false;
	}
}

bool app::gra::Window::initWindow()
{
	typedef SDL_WindowFlags WindowFlags;
	constexpr auto centerPos = SDL_WINDOWPOS_CENTERED;
	constexpr auto windowFlags = WindowFlags::SDL_WINDOW_ALLOW_HIGHDPI | WindowFlags::SDL_WINDOW_SHOWN;
	SDL_Window * pWindow = nullptr;

	pWindow = SDL_CreateWindow(m_title.c_str(), centerPos, centerPos, m_width, m_height, windowFlags);

	const bool success = nullptr != pWindow;
	if (success) { m_window.reset(pWindow); }
	return success;
}

bool app::gra::Window::initRenderer(app::del::UPtrWindow const & uptrSdlWindow)
{
	SDL_Renderer * pRenderer = nullptr;
	
	pRenderer = SDL_CreateRenderer(uptrSdlWindow.get(), -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);

	const bool success = nullptr != pRenderer;
	if (success) { m_renderer.reset(pRenderer, del::SdlDeleter()); }
	return success;
}
