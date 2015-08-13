//Created by Petar Ostojic
//Tue Mar 3 03:57:17 2015
#include "cMusic.h"
#include <SDL2/SDL_mixer.h>
#ifndef CMUSICSDL2_H
#define CMUSICSDL2_H

class cMusicSDL2 : public cMusic{
public:
	cMusicSDL2();
	~cMusicSDL2();

	//Load music file; Returns true, if music was successfully loaded
	bool Load(std::string _filename);
	//Play music; If _repeat == -1, then music will play forever
	//'fade' is time in miliseconds, how long will music fade in 
	//If music is already playing, nothing will happen
	//If music is paused, it will continue playing, but it will not fade in
	void Play(int _repeat = -1, int fade = 0);
	//Stop playing music
	//'fade' is time in miliseconds, how long will music fade in  
	void Stop(int fade = 0);
	//Pause music
	void Pause();
	//Free memory
	void Free();
private:
	Mix_Music *music;
	bool isPaused;
};

#endif