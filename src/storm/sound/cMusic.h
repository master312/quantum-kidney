//Created by Petar Ostojic
//Tue Mar 3 03:53:59 2015
//This class is used for controlling single music file
#include "../defines.h"
#include "../fLogs.h"
#ifndef CMUSIC_H
#define CMUSIC_H

class cMusic{
public:
	//Filename of music file
	std::string filename;

	cMusic();
	virtual ~cMusic();
	//Load music file; Returns true, if music was successfully loaded
	virtual bool Load(std::string _filename);
	//Play music; If _repeat == -1, then music will play forever
	//'fade' is time in miliseconds, how long will music fade in  
	virtual void Play(int _repeat = -1, int fade = 0);
	//Stop playing music
	//'fade' is time in miliseconds, how long will music fade in
	virtual void Stop(int fade = 0);
	//Pause music
	virtual void Pause();
	//Free memory
	virtual void Free();
};

#endif