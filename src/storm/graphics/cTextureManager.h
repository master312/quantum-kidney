//Created by Petar Ostojic
//Tue Feb 17 17:06:05 2015
#include "sTexture.h"
#include <vector>
#include <map>
#include <list>
#include "../defines.h"
#include "../fLogs.h"
#include "cGraphics.h"
#ifndef CTEXTUREMANAGER_H
#define CTEXTUREMANAGER_H
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    #define RMASK 0xff000000
    #define GMASK 0x00ff0000
    #define BMASK 0x0000ff00
    #define AMASK 0x000000ff
#else
    #define RMASK 0x000000ff
    #define GMASK 0x0000ff00
    #define BMASK 0x00ff0000
    #define AMASK 0xff000000
#endif
//TODO: Show system(SDL_MESSAGEBOX) message box / on error ?
class cTextureManager{
public:
	std::map<uint, sTexture*> textures;			//All loaded textures
	std::map<uint, sTextureSection> sections;	//All created sections
	unsigned int memoryUsage;	//In kilobytes

	cTextureManager();
	virtual ~cTextureManager();
	//Initialize texture manager
	//Returns false if there was an error
	virtual bool Initialize();
	virtual void SetGraphics(cGraphics *gr);
	//Loads texture from file
	virtual uint LoadTexture(std::string filename);
	//Loads texture from memory (SDL_Surface)
	//Warning: Surface will not be freed
	virtual uint LoadTextureFromMemory(SDL_Surface *sur, std::string filename = "");
	
	//Reload all textures
	virtual void ReloadTextures();
	//Reloads specified texture
	virtual void ReloadTexture(uint textureId);
	//Unload specified texture
	//All sections of this texture will be deleted
	virtual void UnloadTexture(uint textureId);
	//Remove specified texture section
	virtual void RemoveSection(uint sectionId);

	//Creates texture section;
	//Returns sections ID
	virtual uint CreateSection(uint textureId, int x, int y, int w, int h);
	//Create texture section
	//Returns section id
	virtual uint CreateSection(sTextureSection s);

	//Draw texture on screen
	//X and Y are coordinates on screen
	//S is part of texture to be drawen
	virtual void DrawTexture(uint textureId, int x, int y, float scale = 1, int rot = 0, int opacity = 100);
	//Draw scaled texture. Texture will be scales to .w and .h of destRect
	virtual void DrawTextureScaled(uint textureId, sRect *destRect, int rot = 0, int opacity = 100);
	//Draw cropped texture, cropped from 'srcRect', and drawn to X:Y coordinates
	virtual void DrawTextureCropped(uint textureId, sRect *srcRect, int x, int y, int rot = 0, int opacity = 100);
	//Draws texture section on screen
	virtual void DrawSection(uint sectionId, int x, int y, float scale = 1, int rot = 0, int opacity = 100);
	//Draw scaled texture. Texture will be scales to .w and .h of destRect
	virtual void DrawSectionScaled(uint sectionId, sRect *destRect, int rot = 0, int opacity = 100);
	//Draw cropped texture. Texture will be cropped to crop rect
	virtual void DrawSectionCropped(uint sectionId, sRect *crop, int x, int y, int rot = 0, int opacity = 100);

	//Returns texture width
	int GetTextureWidth(uint textureId);
	//Returns texture height
	int GetTextureHeight(uint textureId);
	//Return memory usage of all loaded textures
	int GetMemoryUsage() { return memoryUsage; }

	//Returns pointer to texture section object, or NULL if none found
	sTextureSection *GetSection(uint sectionId);
	//Returns pointer to texture object, of NULL if none found
	sTexture *GetTexture(uint textureId);

	//Unloads all textures, and delete all sections
	virtual void UnloadAll();
	//Return texture ID if its already been loaded, or zero if texture is not loaded
	virtual uint IsLoaded(std::string filename);
	//Prints memory usage on console
	void PrintMemoryUsage();

	//Generates texture ID for new texture
	uint GenId();

	cGraphics *graphics;
protected:
	//Draws @textureId on screen
	virtual void DrawRaw(uint textureId, int srcX, int srcY, int srcW, int srcH, 
									int destX, int destY, int destW, int destH,
									int rotation, int opacity);

};

#endif