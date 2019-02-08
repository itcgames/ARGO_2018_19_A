#ifndef _FACTORY_LOBBY_SCENE_H
#define _FACTORY_LOBBY_SCENE_H

#include "../EntitiesFactory.h"

namespace app::fact::sce
{
	class LobbySceneFactory : public EntitiesFactory
	{
	public: // Constructors/Destructor/Assignments
		LobbySceneFactory() = default;
		virtual ~LobbySceneFactory() = default;

		LobbySceneFactory(LobbySceneFactory const &) = default;
		LobbySceneFactory & operator=(LobbySceneFactory const &) = default;

		LobbySceneFactory(LobbySceneFactory &&) = default;
		LobbySceneFactory & operator=(LobbySceneFactory &&) = default;

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

#endif // !_FACTORY_LOBBY_SCENE_H
