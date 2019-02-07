#ifndef _FACTORY_LOBBY_SELECT_SCENE_H
#define _FACTORY_LOBBY_SELECT_SCENE_H

#include "../EntitiesFactory.h"
#include "deleters/SdlDeleter.h"

namespace app::fact::sce
{
	class LobbySelectSceneFactory : public EntitiesFactory
	{
	public: // Constructors/Destructor/Assignments
		LobbySelectSceneFactory();
		virtual ~LobbySelectSceneFactory() = default;

		LobbySelectSceneFactory(LobbySelectSceneFactory const &) = default;
		LobbySelectSceneFactory & operator=(LobbySelectSceneFactory const &) = default;

		LobbySelectSceneFactory(LobbySelectSceneFactory &&) = default;
		LobbySelectSceneFactory & operator=(LobbySelectSceneFactory &&) = default;

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

#endif // !_FACTORY_LOBBY_SELECT_SCENE_H
