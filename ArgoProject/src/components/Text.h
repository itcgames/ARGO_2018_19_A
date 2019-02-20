#ifndef _COMP_TEXT_H
#define _COMP_TEXT_H

#include "graphics/Font.h"

namespace app::comp
{
	struct Text
	{
	public: // Constructors/Destructor/Assignments
		Text() = default;
		~Text() = default;

		Text(Text const &) = default;
		Text & operator=(Text const &) = default;

		Text(Text &&) = default;
		Text & operator=(Text &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		std::shared_ptr<app::gra::Font> font;
		std::string string;
		math::Vector2f border;
		SDL_Color color = { 0u, 0u, 0u, 255u };
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

#endif // !_COMP_TEXT_H
