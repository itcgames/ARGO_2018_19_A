#ifndef _FOLLOW_ENTITY_SYSTEM_H
#define _FOLLOW_ENTITY_SYSTEM_H

#include "BaseSystem.h"

namespace app::sys
{
	class FollowEntitySystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		FollowEntitySystem() = default;
		virtual ~FollowEntitySystem() = default;

		FollowEntitySystem(FollowEntitySystem const &) = default;
		FollowEntitySystem & operator=(FollowEntitySystem const &) = default;

		FollowEntitySystem(FollowEntitySystem &&) = default;
		FollowEntitySystem & operator=(FollowEntitySystem &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual void update(app::time::seconds const & dt) final override;
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

#endif // !_FOLLOW_ENTITY_SYSTEM_H
