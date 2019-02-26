#ifndef _SEEK_ENTITY_SYSTEM_H
#define _SEEK_ENTITY_SYSTEM_H

#include "BaseSystem.h"

namespace app::sys
{
	class SeekEntitySystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		SeekEntitySystem() = default;
		~SeekEntitySystem() = default;

		SeekEntitySystem(SeekEntitySystem const &) = default;
		SeekEntitySystem(SeekEntitySystem &&) = default;

		SeekEntitySystem & operator=(SeekEntitySystem const &) = default;
		SeekEntitySystem & operator=(SeekEntitySystem &&) = default;

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

#endif // !_SEEK_ENTITY_SYSTEM_H
