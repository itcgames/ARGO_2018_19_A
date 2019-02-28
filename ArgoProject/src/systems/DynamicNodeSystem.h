#ifndef _DYNAMIC_NODE_SYSTEM_H
#define _DYNAMIC_NODE_SYSTEM_H

#include "BaseSystem.h"

namespace app::sys
{
	class DynamicNodeSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		DynamicNodeSystem() = default;
		virtual ~DynamicNodeSystem() = default;

		DynamicNodeSystem(DynamicNodeSystem const &) = default;
		DynamicNodeSystem & operator=(DynamicNodeSystem const &) = default;

		DynamicNodeSystem(DynamicNodeSystem &&) = default;
		DynamicNodeSystem & operator=(DynamicNodeSystem &&) = default;

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

#endif // !_DYNAMIC_NODE_SYSTEM_H
