#ifndef _TUTORIAL_LEVEL_SCENE_H
#define _TUTORIAL_LEVEL_SCENE_H

#include "BaseScene.h"

namespace app::sce
{
	class TutorialLevelScene : public BaseScene
	{
	public: // Constructors/Destructor/Assignments
		TutorialLevelScene(SceneType & sceneManagerType);
		virtual ~TutorialLevelScene() = default;

		TutorialLevelScene(TutorialLevelScene const &) = default;
		TutorialLevelScene & operator=(TutorialLevelScene const &) = default;

		TutorialLevelScene(TutorialLevelScene &&) = default;
		TutorialLevelScene & operator=(TutorialLevelScene &&) = default;

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

#endif // !_TUTORIAL_LEVEL_SCENE_H
