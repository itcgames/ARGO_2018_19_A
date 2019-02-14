#ifndef _SYSTEM_CURRENTGROUND_H
#define _SYSTEM_CURRENTGROUND_H

#include "BaseSystem.h"

namespace app::sys
{
	class CurrentGroundSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		CurrentGroundSystem () = default;
		~CurrentGroundSystem () = default;

		CurrentGroundSystem (CurrentGroundSystem  const &) = default;
		CurrentGroundSystem  & operator=(CurrentGroundSystem  const &) = default;

		CurrentGroundSystem (CurrentGroundSystem  &&) = default;
		CurrentGroundSystem  & operator=(CurrentGroundSystem  &&) = default;

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

#endif // !_SYSTEM_CURRENTGROUND_H
