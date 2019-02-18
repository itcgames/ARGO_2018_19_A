#ifndef _COMP_PRESSEABLE_H
#define _COMP_PRESSEABLE_H

#include "commands/BaseCommand.h"

namespace app::comp
{
	struct Presseable
	{
	public: // Public typedefs/usings/enums
		enum class State
		{
			Deactive, Active, Highlighted, Pressed
		};
		using KeyCommands = std::map<app::inp::KeyCode, std::shared_ptr<app::cmnd::BaseCommand>>;
		using MouseCommands = std::map<app::inp::MouseButtonCode, std::shared_ptr<app::cmnd::BaseCommand>>;
		using ButtonCommands = std::map<app::inp::ControllerButtonCode, std::shared_ptr<app::cmnd::BaseCommand>>;
	public: // Constructors/Destructor/Assignments
		Presseable() = default;
		~Presseable() = default;

		Presseable(Presseable const &) = default;
		Presseable & operator=(Presseable const &) = default;

		Presseable(Presseable &&) = default;
		Presseable & operator=(Presseable &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		State state;
		std::optional<KeyCommands> keyCommands;
		std::optional<MouseCommands> mouseCommands;
		std::optional<ButtonCommands> buttonCommands;
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

#endif // !_COMP_PRESSEABLE_H
