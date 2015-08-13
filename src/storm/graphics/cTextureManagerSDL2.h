//Thu jun 10 06:12:34 2015
#include "cTextureManager.h"
#include "cGraphicsSDL2.h"
#ifndef CTEXTUREMANAGERSDL2_H
#define CTEXTUREMANAGERSDL2_H

class cTextureManagerSDL2 : public cTextureManager {
public:
	cTextureManagerSDL2();
	~cTextureManagerSDL2();

	//Loads texture from file
	uint LoadTexture(std::string filename);
	//Loads texture from memory (SDL_Surface)
	//Warning: Surface will not be freed
	uint LoadTextureFromMemory(SDL_Surface *sur, std::string filename = "");
	
	//Reload specified texture
	void ReloadTexture(sTexture *tx);
	//Unload specified texture
	//All sections of this texture will be deleted
	void UnloadTexture(uint textureId);
	//Unloads all textures, and delete all sections
	void UnloadAll();
private:
	//Creates SDL_Texture form SDL_Surface and returns it
	SDL_Texture *MakeTexture(SDL_Surface *sur, int &size);
	
	SDL_Rect tmpRenderSrc;
	SDL_Rect tmpRenderDest;
protected:
	void DrawRaw(uint textureId, int srcX, int srcY, int srcW, int srcH, 
								int destX, int destY, int destW, int destH,
								int rotation, int opacity);
};

#endif