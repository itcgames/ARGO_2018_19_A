#ifndef _MOVE_COMMAND_H
#define _MOVE_COMMAND_H

#include "BaseCommand.h"
#include "components/Motion.h"

namespace app::cmnd
{
	class MoveCommand : public BaseCommand
	{
	public: // Constructors/Destructor/Assignments
		MoveCommand(app::Entity const _entity, float _dir, float _speed);
		virtual ~MoveCommand() = default;

		MoveCommand(MoveCommand const &) = default;
		MoveCommand & operator=(MoveCommand const &) = default;

		MoveCommand(MoveCommand &&) = default;
		MoveCommand & operator=(MoveCommand &&) = default;


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
		const float m_direction;
		const float m_speed;
	};
}

#endif // !_MOVE_COMMAND_H
