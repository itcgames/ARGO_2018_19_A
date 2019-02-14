#include "stdafx.h"
#include "SdlTtfDeleter.h"

void app::del::SdlTtfDeleter::operator()(TTF_Font * pFont) const
{
	if (pFont == nullptr) { return; }
	// True Type Font library will sometimes crash on the bottom line.
	//TTF_CloseFont(pFont);
	pFont = nullptr;
}
