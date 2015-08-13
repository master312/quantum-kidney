//Created by Petar Ostojic
//Tue Mar 3 03:14:46 2015
#include <SDL2/SDL_mixer.h>
#include "cSound.h"
#ifndef CSOUNDSDL2_H
#define CSOUNDSDL2_H

class cSoundSDL2 : public cSound{
public:
	cSoundSDL2();
	~cSoundSDL2();

	//Load sound from file
	bool Load(std::string _filename);
	//Play sound. If _repeat is == -1, sound will play forever; Default one time
	void Play(int _repeat = 0);
	//Pause sound
	void Pause();
	//Stop sound
	void Stop();
	//Free used memory
	void Free();
private:
	//Pointer to sound data
	Mix_Chunk *sound;
	//Channel that sound is being played on
	int channel;
};

#endif