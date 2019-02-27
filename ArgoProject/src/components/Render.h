﻿#ifndef _COMPONENT_RENDER_H
#define _COMPONENT_RENDER_H

#include "graphics/Texture.h"

namespace app::comp
{
	struct Render
	{
	public: // Constructors/Destructor/Assignments
		Render() = default;
		~Render() = default;

		Render(Render const &) = default;
		Render(Render &&) = default;

		Render & operator=(Render const &) = default;
		Render & operator=(Render &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		std::shared_ptr<app::gra::Texture> texture;
		std::optional<SDL_Rect> source;
		math::Vector2f border;
		math::Vector2f offset;
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_COMPONENT_RENDER_H
