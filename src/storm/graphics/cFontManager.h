//Created by Petar Ostojic
//Fri Feb 20 02:57:05 2015
//This is template class for font manager
#include "../defines.h"
#include "cTextureManager.h"
#include "../fLogs.h"
#include "sFont.h"
#include <map>
#include <SDL2/SDL_ttf.h>
#include <vector>
#ifndef CFONTMANAGER_H
#define CFONTMANAGER_H
/* TODO:
* OPTIMISE GetTextSize() function
* Check if font is already loaded
* Cleanup code and optimize
* Big Optimization: Dont draw text if its bigger then screen
*/

class cFontManager{
public:
	cFontManager(){}
	virtual ~cFontManager(){}
	//Pointer to texture manager
	cTextureManager *tManager;
	//Vector of loaded fonts
	std::map<std::string, sFont> fonts;
	//String(array) of character to be generated
	std::string chars;
	//Default font spacing
	static const int DEF_SPACING = 2;

	//Initialize font system
	//Return true if system was successful initialized 
	virtual bool Initialize();
	//Set list of characters to be generated
	void SetChars(std::string s);
	//Loads font from file
	//Return true if font is loaded successfully
	virtual bool LoadFont(std::string filename, std::string fontName, int size);
	//Change letter spacing on font matching fontName
	virtual void SetLetterSpacing(std::string fontName, int spacing);

	//Unload specified font
	virtual void UnloadFont(std::string fontName);
	//Unload all loaded fonts
	virtual void UnloadAll();

	//Draw text on screen
	virtual void DrawText(std::string font, std::string text, int x, int y, 
										float r = 0, float g = 0, float b = 0, 
										float scale = 0, float rotation = 0);

	//Returns size of string in pixels, when drawn using specified font
	virtual sRect GetTextSize(std::string text, std::string font);
	virtual void DrawSection(uint section, int x, int y, float scale, 
									float rotation,  float r, float g, float b);
	//Return pointer to font
	sFont *GetFont(std::string fontName);
	int GetFontsCount() { return fonts.size(); }
private:
	//Generate new sFont
	sFont GenerateFont(TTF_Font *font, int size);
	//Check if character at location 'ch' is ASCII or UTF8
	//Return true if character is utf8
	bool IsUtf8(std::string str, int ch);
};

#endif