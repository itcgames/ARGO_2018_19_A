#ifndef _FACTORY_LOADING_SCENE_H
#define _FACTORY_LOADING_SCENE_H

#include "../EntitiesFactory.h"

namespace app::fact::sce
{
	class LoadingSceneFactory : public EntitiesFactory	
	{
	public: // Constructors/Destructor/Assignments
		LoadingSceneFactory() = default;
		~LoadingSceneFactory() = default;

		LoadingSceneFactory(LoadingSceneFactory const &) = default;
		LoadingSceneFactory & operator=(LoadingSceneFactory const &) = default;

		LoadingSceneFactory(LoadingSceneFactory &&) = default;
		LoadingSceneFactory & operator=(LoadingSceneFactory &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual std::vector<app::Entity> create() final override;
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

#endif // !_FACTORY_LOADING_SCENE_H
