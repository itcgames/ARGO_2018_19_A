#ifndef _COMP_WIDGET_H
#define _COMP_WIDGET_H

namespace app::comp
{
	struct Widget
	{
	public: // Public typedefs/usings/enums
		enum class State
		{
			Deactive, Active, Highlighted, Pressed
		};
	public: // Constructors/Destructor/Assignments
		Widget() = default;
		~Widget() = default;

		Widget(Widget const &) = default;
		Widget & operator=(Widget const &) = default;

		Widget(Widget &&) = default;
		Widget & operator=(Widget &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		State state = State::Deactive;
		std::optional<app::Entity> up = std::nullopt
			, down = std::nullopt
			, left = std::nullopt
			, right = std::nullopt;
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

#endif // !_COMP_WIDGET_H
