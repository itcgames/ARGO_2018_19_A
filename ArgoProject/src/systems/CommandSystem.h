#ifndef _SYS_COMMAND_SYSTEM_H
#define _SYS_COMMAND_SYSTEM_H

#include "BaseSystem.h"

namespace app::sys
{
	class CommandSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		CommandSystem() = default;
		virtual ~CommandSystem() = default;

		CommandSystem(CommandSystem const &) = default;
		CommandSystem & operator=(CommandSystem const &) = default;

		CommandSystem(CommandSystem &&) = default;
		CommandSystem & operator=(CommandSystem &&) = default;


	public: // Public Static Functions
	public: // Public Member Functions
		// Inherited via BaseSystem
		virtual void update(app::time::seconds const & dt) override;
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

	};
}

#endif // !_SYS_COMMAND_SYSTEM_H
