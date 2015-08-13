//Created by Petar Ostojic
//Fri Feb 27 02:25:09 2015
//This class is used for controlling and storing one sound effect
#include "../defines.h"
#include "../fLogs.h"
#ifndef CSOUND_H
#define CSOUND_H

class cSound{
public:
	//Name of sound file
	std::string filename;

	cSound();
	virtual ~cSound();

	//Load sound from file; Return true, if sound was successfully loaded
	virtual bool Load(std::string _filename);
	//Play sound. If _repeat is == -1, sound will play forever
	virtual void Play(int _repeat = 0);
	//Pause sound
	virtual void Pause();
	//Stop sound
	virtual void Stop();
	//Free used memory
	virtual void Free();
};


#endif