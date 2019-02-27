﻿#ifndef _RESOURCES_TEXTURE_KEY_H
#define _RESOURCES_TEXTURE_KEY_H

namespace app::res
{
	enum class TextureKey
	{
		Debug,
		DebugBig,
		DebugHuge,
		DebugAnimation,
		DebugEnemyAnimation,
		AxeRun,
		EnemyWalk,
		HazardSpikes,
		LevelWall,
		Loading,
		Splash,
		PlatformLeft,
		PlatformMiddle,
		PlatformRight,
		DebugCollisionBox,
		Count // Keep this one at the bottom of the enum list
	};
}

#endif // !_RESOURCES_TEXTURE_KEY_H
