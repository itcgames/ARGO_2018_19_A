#ifndef _DROP_COMMAND_H
#define _DROP_COMMAND_H

#include "BaseCommand.h"

namespace app::cmnd
{
	class DropCommand : public BaseCommand
	{
	public: // Constructors/Destructor/Assignments
		DropCommand(app::Entity const _entity);
		~DropCommand() = default;

		DropCommand(DropCommand const &) = default;
		DropCommand & operator=(DropCommand const &) = default;

		DropCommand(DropCommand &&) = default;
		DropCommand & operator=(DropCommand &&) = default;

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
	};
}

#endif // !_DROP_COMMAND_H
