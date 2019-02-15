#ifndef _SYSTEM_AI_H
#define _SYSTEM_AI_H

#include "BaseSystem.h"

namespace app::sys
{
	class AISystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		AISystem() = default;
		~AISystem() = default;

		AISystem(AISystem const &) = default;
		AISystem & operator=(AISystem const &) = default;

		AISystem(AISystem &&) = default;
		AISystem & operator=(AISystem &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
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

#endif // !_SYSTEM_AI_H
