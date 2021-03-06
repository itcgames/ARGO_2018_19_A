﻿#ifndef _FACTORY_MULTIPLAYER_LEVEL_SCENE_H
#define _FACTORY_MULTIPLAYER_LEVEL_SCENE_H

#include "../SceneFactory.h"

namespace app::fact::sce
{
	class MultiplayerLevelSceneFactory : public SceneFactory
	{
	public: // Constructors/Destructor/Assignments
		MultiplayerLevelSceneFactory() = default;
		virtual ~MultiplayerLevelSceneFactory() = default;

		MultiplayerLevelSceneFactory(MultiplayerLevelSceneFactory const &) = default;
		MultiplayerLevelSceneFactory & operator=(MultiplayerLevelSceneFactory const &) = default;

		MultiplayerLevelSceneFactory(MultiplayerLevelSceneFactory &&) = default;
		MultiplayerLevelSceneFactory & operator=(MultiplayerLevelSceneFactory &&) = default;

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

#endif // !_FACTORY_MULTIPLAYER_LEVEL_SCENE_H
