#ifndef _SYSTEMS_ANIMATOR_H
#define _SYSTEMS_ANIMATOR_H

#include "BaseSystem.h"

namespace app::sys
{
	class AnimatorSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		AnimatorSystem() = default;
		virtual ~AnimatorSystem() = default;

		AnimatorSystem(AnimatorSystem const &) = default;
		AnimatorSystem & operator=(AnimatorSystem const &) = default;

		AnimatorSystem(AnimatorSystem &&) = default;
		AnimatorSystem & operator=(AnimatorSystem &&) = default;

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

#endif // !_SYSTEMS_ANIMATOR_H
