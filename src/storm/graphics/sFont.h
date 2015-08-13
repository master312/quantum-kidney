//Created by Petar Ostojic
//Fri Feb 20 02:52:01 2015
#include "../defines.h"
#include "cTextureManager.h"
#ifndef SFONT_H
#define SFONT_H

struct sFont{
	int spacing;	//Size of space, is spacing * 4
	std::string name;
	uint texture;
	int newLine;	//Height of line
	int size;
	short r, g, b;
	std::map<std::string, uint> glyphs;	//Map of texture sections
	sFont(){ }
};

#endif