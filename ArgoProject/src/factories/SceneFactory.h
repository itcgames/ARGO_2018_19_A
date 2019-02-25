#ifndef _SCENE_FACTORY_H
#define _SCENE_FACTORY_H

#include "EntitiesFactory.h"
#include "graphics/AudioPlayer.h"

namespace app::fact::sce
{
	class SceneFactory : public EntitiesFactory
	{
	public: // Constructors/Destructor/Assignments
		SceneFactory();
		virtual ~SceneFactory() = default;

		SceneFactory(SceneFactory const &) = default;
		SceneFactory & operator=(SceneFactory const &) = default;

		SceneFactory(SceneFactory &&) = default;
		SceneFactory & operator=(SceneFactory &&) = default;

	public: // Public Static Functions
	public: // Public Member Functions
	public: // Public Static Variables
	public: // Public Member Variables
	protected: // Protected Static Functions
	protected: // Protected Member Functions
	protected: // Protected Static Variables
	protected: // Protected Member Variables
		app::gra::AudioPlayer & m_audioPlayer;
	private: // Private Static Functions
	private: // Private Member Functions
	private: // Private Static Variables
	private: // Private Member Variables
	};
}

#endif // !_SCENE_FACTORY_H
