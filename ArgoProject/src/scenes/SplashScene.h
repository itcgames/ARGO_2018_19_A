#ifndef _SPLASH_SCENE_H
#define _SPLASH_SCENE_H

#include "BaseScene.h"

namespace app::sce
{
	class SplashScene : public BaseScene
	{
	public: // Constructors/Destructor/Assignments
		SplashScene(SceneType & sceneManagerType);
		virtual ~SplashScene();

		SplashScene(SplashScene const &) = default;
		SplashScene & operator=(SplashScene const &) = default;

		SplashScene(SplashScene &&) = default;
		SplashScene & operator=(SplashScene &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
		virtual void start() final override;
		virtual void end() final override;
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

#endif // !_SPLASH_SCENE_H
