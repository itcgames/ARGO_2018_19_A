#ifndef _ATTACK_COMMAND_H
#define _ATTACK_COMMAND_H

#include "BaseCommand.h"

namespace app::cmnd
{
	class AttackCommand : public BaseCommand
	{
	public: // Constructors/Destructor/Assignments
		AttackCommand(app::Entity const _entity);
		virtual ~AttackCommand() = default;

		AttackCommand(AttackCommand const &) = default;
		AttackCommand & operator=(AttackCommand const &) = default;

		AttackCommand(AttackCommand &&) = default;
		AttackCommand & operator=(AttackCommand &&) = default;


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

#endif // !_ATTACK_COMMAND_H
