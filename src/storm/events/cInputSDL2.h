//Created by Petar Ostojic
//Tue Feb 24 01:05:18 2015
#include "cInput.h"
#ifndef CINPUTSDL2_H
#define CINPUTSDL2_H

class cInputSDL2 : public cInput{
public:
	cInputSDL2();
	~cInputSDL2();
	bool Update();
private:
	SDL_Event EVENT;
};

#endif