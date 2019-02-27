#ifndef _DISC_RETURN_SYSTEM_H	
#define _DISC_RETURN_SYSTEM_H

#include "BaseSystem.h"

namespace app::sys
{
	class DiscReturnSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		DiscReturnSystem() = default;
		virtual ~DiscReturnSystem() = default;

		DiscReturnSystem(DiscReturnSystem const &) = default;
		DiscReturnSystem & operator=(DiscReturnSystem const &) = default;

		DiscReturnSystem(DiscReturnSystem &&) = default;
		DiscReturnSystem & operator=(DiscReturnSystem &&) = default;

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
		const int SPEED_CUTOFF = 10;
	};
}

#endif // !_DISC_RETURN_SYSTEM_H
