#ifndef _LEVEL_SELECT_SCENE_H
#define _LEVEL_SELECT_SCENE_H

#include "BaseScene.h"

namespace app::sce
{
	class LevelSelectScene : public BaseScene
	{
	public: // Constructors/Destructor/Assignments
		LevelSelectScene(SceneType & sceneManagerType);
		virtual ~LevelSelectScene() = default;

		LevelSelectScene(LevelSelectScene const &) = default;
		LevelSelectScene & operator=(LevelSelectScene const &) = default;

		LevelSelectScene(LevelSelectScene &&) = default;
		LevelSelectScene & operator=(LevelSelectScene &&) = default;

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

#endif // !_LEVEL_SELECT_SCENE_H
