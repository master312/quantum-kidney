#include "cFontManagerSDL2.h"

cFontManagerSDL2::cFontManagerSDL2(cTextureManager *tm){
	tManager = tm;
}
cFontManagerSDL2::~cFontManagerSDL2(){
	UnloadAll();	
	TTF_Quit();
}

void cFontManagerSDL2::DrawSection(uint section, int x, int y, float scale, 
									float rotation, float r, float g, float b){
	if(scale <= 0)
		scale = 1.0;
	
	uint textureId = 0;
	if(tManager->GetSection(section) == NULL){
		StormPrintLog(STORM_LOG_WARNING, "cFontManagerSDL2", 
				"No section with ID %d", section);
		return;
	}
	sTextureSection *tmpS = tManager->GetSection(section);
	textureId = tmpS->texture;
	sTexture *tmpT = tManager->GetTexture(textureId);
	SDL_SetTextureColorMod(tmpT->sdlTexture, r * 255, g * 255, b * 255);
	tManager->DrawSection(section, x, y);
}