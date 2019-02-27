#ifndef _LOADING_SYSTEM_H
#define _LOADING_SYSTEM_H

#include "BaseSystem.h"

namespace app::sys
{
	class LoadingSystem : public BaseSystem
	{
	public: // Constructors/Destructor/Assignments
		LoadingSystem() = default;
		virtual ~LoadingSystem() = default;

		LoadingSystem(LoadingSystem const &) = default;
		LoadingSystem & operator=(LoadingSystem const &) = default;

		LoadingSystem(LoadingSystem &&) = default;
		LoadingSystem & operator=(LoadingSystem &&) = default;


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

#endif // !_LOADING_SYSTEM_H
