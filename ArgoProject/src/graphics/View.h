#ifndef _GRAPHICS_VIEW_H
#define _GRAPHICS_VIEW_H

namespace app::gra
{
	class View
	{
	public: // Constructors/Destructor/Assignments
		View() = default;
		~View() = default;

		View(View const &) = default;
		View & operator=(View const &) = default;

		View(View &&) = default;
		View & operator=(View &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		math::Vector2i position;
		math::Vector2i size;
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

#endif // !_GRAPHICS_VIEW_H
