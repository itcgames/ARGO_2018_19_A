#ifndef _CREDITS_SCENE_H
#define _CREDITS_SCENE_H

#include "BaseScene.h"

namespace app::sce
{
	class CreditsScene : public BaseScene
	{
	public: // Constructors/Destructor/Assignments
		CreditsScene(SceneType & sceneManagerType);
		virtual ~CreditsScene() = default;

		CreditsScene(CreditsScene const &) = default;
		CreditsScene & operator=(CreditsScene const &) = default;

		CreditsScene(CreditsScene &&) = default;
		CreditsScene & operator=(CreditsScene &&) = default;

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

#endif // !_CREDITS_SCENE_H
