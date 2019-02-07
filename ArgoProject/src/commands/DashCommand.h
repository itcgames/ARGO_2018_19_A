#ifndef _DASH_COMMAND_H
#define _DASH_COMMAND_H

#include "BaseCommand.h"

namespace app::cmnd
{
	class DashCommand : public BaseCommand
	{
	public: // Constructors/Destructor/Assignments
		DashCommand(app::Entity const _entity);
		virtual ~DashCommand() = default;

		DashCommand(DashCommand const &) = default;
		DashCommand & operator=(DashCommand const &) = default;

		DashCommand(DashCommand &&) = default;
		DashCommand & operator=(DashCommand &&) = default;


	public: // Public Static Functions
	public: // Public Member Functions
		virtual void execute() override;
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
		app::Entity const m_entity;
		bool m_isRight;
		app::inp::KeyHandler & m_keyHandler;
	};
}

#endif // !_DASH_COMMAND_H
