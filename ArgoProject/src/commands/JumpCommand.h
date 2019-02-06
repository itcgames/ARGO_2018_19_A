#ifndef _JUMP_COMMAND_H
#define _JUMP_COMMAND_H

#include "BaseCommand.h"

namespace app::cmnd
{
	class JumpCommand : public BaseCommand
	{
	public: // Constructors/Destructor/Assignments
		JumpCommand(app::Entity const _entity, float _force);
		virtual ~JumpCommand() = default;

		JumpCommand(JumpCommand const &) = default;
		JumpCommand & operator=(JumpCommand const &) = default;

		JumpCommand(JumpCommand &&) = default;
		JumpCommand & operator=(JumpCommand &&) = default;


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
		float m_force;
	};
}

#endif // !_JUMP_COMMAND_H
