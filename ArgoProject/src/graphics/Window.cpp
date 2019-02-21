#include "stdafx.h"
#include "Window.h"

app::gra::Window::Window(
	app::inp::KeyHandler & keyHandler
	, app::inp::MouseHandler & mouseHandler
	, app::inp::ControllerHandler & controllerHandler
	, app::gra::WindowParameters params
)
	: m_keyhandler(keyHandler)
	, m_mousehandler(mouseHandler)
	, m_controllerHandler(controllerHandler)
	, m_open(true)
	, m_title(params.title)
	, m_width(params.width)
	, m_height(params.height)
	, m_view{ {params.width / 2, params.height / 2}, {params.width, params.height} }
	, m_window(nullptr)
	, m_renderer(nullptr)
{
	m_open = this->init();
}

app::gra::Window::~Window()
{
}

void app::gra::Window::setView(app::gra::View const & view)
{
	m_view = view;
}

void app::gra::Window::resetView()
{
	m_view = app::gra::View{ {m_width / 2, m_height / 2}, {m_width, m_height} };
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
		case EventType::SDL_CONTROLLERBUTTONUP:
			m_controllerHandler.updateButton(sdlEvent.cbutton.which, static_cast<app::inp::ControllerButtonCode>(sdlEvent.cbutton.button), false);
			break;
		case EventType::SDL_CONTROLLERBUTTONDOWN:
			m_controllerHandler.updateButton(sdlEvent.cbutton.which, static_cast<app::inp::ControllerButtonCode>(sdlEvent.cbutton.button), true);
			break;
		case EventType::SDL_CONTROLLERAXISMOTION:
			m_controllerHandler.updateAxis(sdlEvent.caxis.which, static_cast<app::inp::ControllerAxisCode>(sdlEvent.caxis.axis), sdlEvent.caxis.value);
			break;
		case EventType::SDL_CONTROLLERDEVICEADDED:
			m_controllerHandler.addController(sdlEvent.cdevice.which);
			break;
		case EventType::SDL_CONTROLLERDEVICEREMOVED:
			m_controllerHandler.removeController(sdlEvent.cdevice.which);
			break;
		default:
			break;
		}
	}
}

void app::gra::Window::clear() const
{
	auto lock = std::lock_guard<decltype(app::gra::Texture::s_sdlMutex)>(app::gra::Texture::s_sdlMutex);
	SDL_SetRenderDrawColor(m_renderer.get(), s_BG_COLOR.r, s_BG_COLOR.g, s_BG_COLOR.b, s_BG_COLOR.a);
	SDL_RenderClear(m_renderer.get());
}

void app::gra::Window::render(app::gra::RenderRect const & rect) const
{
	constexpr auto FLIP_FLAG = SDL_RendererFlip::SDL_FLIP_NONE;
	auto const & position = static_cast<math::Vector2i>(rect.getPosition());
	auto const & origin = static_cast<math::Vector2i>(rect.getOrigin());
	auto const & size = static_cast<math::Vector2i>(rect.getSize());
	auto const & source = rect.getSourceRect();
	auto const & screenSize = math::Vector2f{ static_cast<float>(m_width), static_cast<float>(m_height) };
	auto const & scale = screenSize / static_cast<math::Vector2f>(m_view.size);
	auto const & halfSize = m_view.size / 2;
	auto const & destination = SDL_Rect{
		position.x - origin.x - (m_view.position.x - halfSize.x),
		position.y - origin.y - (m_view.position.y - halfSize.y),
		static_cast<int32_t>(size.x * scale.x),
		static_cast<int32_t>(size.y * scale.y)
	};
	auto const & center = SDL_Point{
		static_cast<int32_t>(origin.x * scale.x),
		static_cast<int32_t>(origin.y * scale.y)
	};

	SDL_RenderCopyEx(m_renderer.get(), rect.getTexture(), source.has_value() ? &source.value() : nullptr, &destination, rect.getRotation(), &center, FLIP_FLAG);
}

void app::gra::Window::render(app::gra::RenderText const & rect) const
{
	constexpr auto FLIP_FLAG = SDL_RendererFlip::SDL_FLIP_NONE;
	auto const & position = static_cast<math::Vector2i>(rect.getPosition());
	auto const & origin = static_cast<math::Vector2i>(rect.getOrigin());
	auto const & size = static_cast<math::Vector2i>(rect.getSize());
	auto const & source = rect.getSourceRect();
	auto const & screenSize = math::Vector2f{ static_cast<float>(m_width), static_cast<float>(m_height) };
	auto const & scale = screenSize / static_cast<math::Vector2f>(m_view.size);
	auto const & halfSize = m_view.size / 2;
	auto const & destination = SDL_Rect{
		position.x - origin.x - (m_view.position.x - halfSize.x),
		position.y - origin.y - (m_view.position.y - halfSize.y),
		static_cast<int32_t>(size.x * scale.x),
		static_cast<int32_t>(size.y * scale.y)
	};
	auto const & center = SDL_Point{
		static_cast<int32_t>(origin.x * scale.x),
		static_cast<int32_t>(origin.y * scale.y)
	};

	SDL_RenderCopyEx(m_renderer.get(), rect.getTexture(), source.has_value() ? &source.value() : nullptr, &destination, rect.getRotation(), &center, FLIP_FLAG);
}

void app::gra::Window::render(std::unique_ptr<SDL_Texture> const & texture, SDL_Rect const & rect, std::optional<SDL_Rect> source) const
{
	SDL_RenderCopy(m_renderer.get(), texture.get(), source.has_value() ? &source.value() : nullptr, &rect);
}

void app::gra::Window::render(std::shared_ptr<SDL_Texture> texture, SDL_Rect const & rect, std::optional<SDL_Rect> source) const
{
	SDL_RenderCopy(m_renderer.get(), texture.get(), source.has_value() ? &source.value() : nullptr, &rect);
}

void app::gra::Window::display() const
{
	auto lock = std::lock_guard<decltype(app::gra::Texture::s_sdlMutex)>(app::gra::Texture::s_sdlMutex);
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
	if (success) { m_renderer.reset(pRenderer); }
	return success;
}
