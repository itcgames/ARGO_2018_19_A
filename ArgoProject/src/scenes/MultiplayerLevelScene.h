#ifndef _MULTIPLAYER_LEVEL_SCENE_H
#define _MULTIPLAYER_LEVEL_SCENE_H

#include "BaseScene.h"

namespace app::sce
{
	class MultiplayerLevelScene : public BaseScene
	{
	public: // Constructors/Destructor/Assignments
		MultiplayerLevelScene(SceneType & sceneManagerType);
		virtual ~MultiplayerLevelScene() = default;

		MultiplayerLevelScene(MultiplayerLevelScene const &) = default;
		MultiplayerLevelScene & operator=(MultiplayerLevelScene const &) = default;

		MultiplayerLevelScene(MultiplayerLevelScene &&) = default;
		MultiplayerLevelScene & operator=(MultiplayerLevelScene &&) = default;

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

#endif // !_MULTIPLAYER_LEVEL_SCENE_H
