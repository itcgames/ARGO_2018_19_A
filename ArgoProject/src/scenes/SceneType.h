#ifndef _SCENE_TYPE_H
#define _SCENE_TYPE_H

namespace app::sce
{
	enum class SceneType
	{
		CharacterSelect,
		Credits,
		Level,
		LevelSelect,
		MainMenu,
		LobbySelect,
		Lobby,
		MultiplayerLevel,
		TutorialLevel,
		Splash,
		Loading,
		Count
	};
}

#endif // !_SCENE_TYPE_H
