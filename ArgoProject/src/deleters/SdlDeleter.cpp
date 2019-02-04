#include "stdafx.h"
#include "SdlDeleter.h"

void app::del::SdlDeleter::operator()(SDL_Window * pWindow) const
{
	if (pWindow == nullptr) { return; }
	SDL_DestroyWindow(pWindow);
}

void app::del::SdlDeleter::operator()(SDL_Renderer * pRenderer) const
{
	if (pRenderer == nullptr) { return; }
	SDL_DestroyRenderer(pRenderer);
}

void app::del::SdlDeleter::operator()(SDL_Texture * pTexture) const
{
	if (pTexture == nullptr) { return; }
	SDL_DestroyTexture(pTexture);
}

void app::del::SdlDeleter::operator()(SDL_Surface * pSurface) const
{
	if (pSurface == nullptr) { return; }
	SDL_FreeSurface(pSurface);
}

void app::del::SdlDeleter::operator()(SDL_GameController * pGameController) const
{
	if (pGameController == nullptr) { return; }
	SDL_GameControllerClose(pGameController);
}

void app::del::SdlDeleter::operator()(SDL_Haptic * pHaptic) const
{
	if (pHaptic == nullptr) { return; }
	SDL_HapticClose(pHaptic);
}
