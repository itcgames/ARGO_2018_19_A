#ifndef _LOBBY_SELECT_SCENE_H
#define _LOBBY_SELECT_SCENE_H

#include "BaseScene.h"
#include "network/Client.h"

namespace app::sce
{
	class LobbySelectScene : public BaseScene
	{
	public: // Constructors/Destructor/Assignments
		LobbySelectScene(SceneType & sceneManagerType);
		virtual ~LobbySelectScene() = default;

		LobbySelectScene(LobbySelectScene const &) = default;
		LobbySelectScene & operator=(LobbySelectScene const &) = default;

		LobbySelectScene(LobbySelectScene &&) = default;
		LobbySelectScene & operator=(LobbySelectScene &&) = default;

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

#endif // !_LOBBY_SELECT_SCENE_H
