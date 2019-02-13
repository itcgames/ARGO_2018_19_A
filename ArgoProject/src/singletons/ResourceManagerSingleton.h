#ifndef _SINGLETON_RESOURCE_MANAGER_H
#define _SINGLETON_RESOURCE_MANAGER_H

#include "resources/ResourceManager.h"

namespace app::sin
{
	class ResourceManager
	{
	private: // Constructors/Destructor/Assignments
		ResourceManager() = default;
		~ResourceManager() = default;

		ResourceManager(ResourceManager const &) = default;
		ResourceManager & operator=(ResourceManager const &) = default;

		ResourceManager(ResourceManager &&) = default;
		ResourceManager & operator=(ResourceManager &&) = default;

	public: // Public Static Functions
		static res::ResourceManager<true> & get();
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
		static std::unique_ptr<res::ResourceManager<true>> s_resourceManager;
	private: // Private Member Variables
	};
}

#endif // !_SINGLETON_RESOURCE_MANAGER_H
