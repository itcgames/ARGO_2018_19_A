#ifndef _RESOURCE_LOADER_H
#define _RESOURCE_LOADER_H

#include "graphics/Texture.h"
#include "singletons/WindowSingleton.h"

namespace app::res
{
	template<typename _Resource>
	class ResourceLoader
	{
	private: // Private typedefs/enums/usings
	public: // Constructors/Destructor/Assignments
		ResourceLoader() = default;
		~ResourceLoader() = default;

		ResourceLoader(ResourceLoader const &) = default;
		ResourceLoader & operator=(ResourceLoader const &) = default;

		ResourceLoader(ResourceLoader &&) = default;
		ResourceLoader & operator=(ResourceLoader &&) = default;

	public: // Public Static Functions
		static void load(std::shared_ptr<_Resource> resource, std::string const & file);
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
	private: // Private Member Variables
	};
}


#endif // !_RESOURCE_LOADER_H
