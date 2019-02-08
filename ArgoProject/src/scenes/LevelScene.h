﻿#ifndef _LEVEL_SCENE_H
#define _LEVEL_SCENE_H

#include "BaseScene.h"

namespace app::sce
{
	class LevelScene : public BaseScene
	{
	public: // Constructors/Destructor/Assignments
		LevelScene(SceneType & sceneManagerType);
		virtual ~LevelScene() = default;

		LevelScene(LevelScene const &) = default;
		LevelScene & operator=(LevelScene const &) = default;

		LevelScene(LevelScene &&) = default;
		LevelScene & operator=(LevelScene &&) = default;

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

#endif // !_LEVEL_SCENE_H
