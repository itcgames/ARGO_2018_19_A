#ifndef _LOBBY_SCENE_H
#define _LOBBY_SCENE_H

#include "BaseScene.h"

namespace app::sce
{
	class LobbyScene : public BaseScene
	{
	public: // Constructors/Destructor/Assignments
		LobbyScene(SceneType & sceneManagerType);
		virtual ~LobbyScene() = default;

		LobbyScene(LobbyScene const &) = default;
		LobbyScene & operator=(LobbyScene const &) = default;

		LobbyScene(LobbyScene &&) = default;
		LobbyScene & operator=(LobbyScene &&) = default;

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

#endif // !_LOBBY_SCENE_H
