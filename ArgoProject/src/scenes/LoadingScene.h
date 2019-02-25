#ifndef _LOADING_SCENE_H
#define _LOADING_SCENE_H

#include "BaseScene.h"

namespace app::sce
{
	class LoadingScene : public BaseScene
	{
	public: // Constructors/Destructor/Assignments
		LoadingScene(SceneType & sceneManagerType);
		virtual ~LoadingScene() = default;

		LoadingScene(LoadingScene const &) = default;
		LoadingScene & operator=(LoadingScene const &) = default;

		LoadingScene(LoadingScene &&) = default;
		LoadingScene & operator=(LoadingScene &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual void start() final override;
		virtual void end() final override;
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

#endif // !_LOADING_SCENE_H
