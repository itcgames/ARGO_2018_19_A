#ifndef _CHARACTER_SELECT_SCENE_H
#define _CHARACTER_SELECT_SCENE_H

#include "BaseScene.h"

namespace app::sce
{
	class CharacterSelectScene : public BaseScene
	{
	public: // Constructors/Destructor/Assignments
		CharacterSelectScene(SceneType & sceneManagerType);
		virtual ~CharacterSelectScene();

		CharacterSelectScene(CharacterSelectScene const &) = default;
		CharacterSelectScene & operator=(CharacterSelectScene const &) = default;

		CharacterSelectScene(CharacterSelectScene &&) = default;
		CharacterSelectScene & operator=(CharacterSelectScene &&) = default;

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

#endif // !_CHARACTER_SELECT_SCENE_H
