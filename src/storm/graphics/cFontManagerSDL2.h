//Created by Petar Ostojic
//Fri jun 10 09:37:11 2015
#include "cFontManager.h"
#include "cTextureManagerSDL2.h"
#ifndef CFONTMANAGERSDL2_H
#define CFONTMANAGERSDL2_H

class cFontManagerSDL2 : public cFontManager{
public:
	cFontManagerSDL2(cTextureManager *tm);
	~cFontManagerSDL2();
	void DrawSection(uint section, int x, int y, float scale, float rotation, 
			float r, float g, float b);
};

#endif