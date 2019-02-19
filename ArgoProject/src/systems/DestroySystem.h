#ifndef _DESTROY_SYSTEM_H
#define _DESTROY_SYSTEM_H

#include "BaseSystem.h"

namespace app::sys
{
	class DestroySystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		DestroySystem() = default;
		virtual ~DestroySystem() = default;

		DestroySystem(DestroySystem const &) = default;
		DestroySystem & operator=(DestroySystem const &) = default;

		DestroySystem(DestroySystem &&) = default;
		DestroySystem & operator=(DestroySystem &&) = default;

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

#endif // !_DESTROY_SYSTEM_H
