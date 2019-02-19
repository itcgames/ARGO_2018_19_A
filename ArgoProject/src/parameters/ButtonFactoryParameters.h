#ifndef _BUTTON_FACTORY_PARAMETERS_H
#define _BUTTON_FACTORY_PARAMETERS_H

#include "commands/BaseCommand.h"
#include "components/Widget.h"

namespace app::par
{
	struct ButtonFactoryParameters
	{
	public: // Constructors/Destructor/Assignments
		ButtonFactoryParameters() = default;
		~ButtonFactoryParameters() = default;

		ButtonFactoryParameters(ButtonFactoryParameters const &) = default;
		ButtonFactoryParameters & operator=(ButtonFactoryParameters const &) = default;

		ButtonFactoryParameters(ButtonFactoryParameters &&) = default;
		ButtonFactoryParameters & operator=(ButtonFactoryParameters &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
		math::Vector2f position;
		math::Vector2f size;
		math::Vector2f border;
		std::string text;
		std::shared_ptr<app::cmnd::BaseCommand> command;
		app::comp::Widget::State state;
		std::optional<app::Entity> entity;
		std::optional<app::Entity> up, down, left, right;
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

#endif // !_BUTTON_FACTORY_PARAMETERS_H
