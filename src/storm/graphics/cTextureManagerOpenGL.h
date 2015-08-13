//Created by Petar Ostojic
//Thu Feb 19 03:42:58 2015
#include "cTextureManager.h"
#ifndef CTEXTUREMANAGEROPENGL_H
#define CTEXTUREMANAGEROPENGL_H
#if BUILD_OPENGL > 0
//TODO: Write this class better, so that you dont have 50 lines of code if every 
//draw function

class cTextureManagerOpenGL : public cTextureManager{
public:
	cTextureManagerOpenGL();
	~cTextureManagerOpenGL();

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
	//Convert surface to gl texture; Return GL texture ID
	//Size will be amount of memory usage in bytes
	//Warning: Surface will not be freed
	uint MakeTexture(SDL_Surface *sur, int &size);
	float currentColor[4];
protected:
	void DrawRaw(uint textureId, int srcX, int srcY, int srcW, int srcH, 
									int destX, int destY, int destW, int destH,
									int rotation, int opacity);
};

#endif
#endif