//Created by Petar Ostojic
//Fri Feb 20 03:18:05 2015
#include "cFontManager.h"
#ifndef CFONTMANAGEROPENGL_H
#define CFONTMANAGEROPENGL_H
#if BUILD_OPENGL > 0

class cFontManagerOpenGL : public cFontManager{
public:
	cFontManagerOpenGL(cTextureManager *tm);
	~cFontManagerOpenGL();
	void DrawSection(uint section, int x, int y, float scale, float rotation, 
			float r, float g, float b);
};

#endif
#endif