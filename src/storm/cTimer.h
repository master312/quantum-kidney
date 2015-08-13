//Created by Petar Ostojic
//Tue Feb 24 04:17:57 2015
//Warning! This class is not compatible with non SDL platforms
//It will need rewrite in order to work with non SDL platforms 
#include "defines.h"
#ifndef CTIMER_H
#define CTIMER_H

class cTimer{
public:
	cTimer();
	cTimer(Uint32 _interval);
	~cTimer();
	//Sets interval (in milliseconds) on what timer will tick
	void SetInterval(Uint32 _interval) { interval = _interval; } 
	//Reset timer to zero, so it can begin to tick again
	void Reset();
	void Stop() { startTime = 0; }
	//Return true if time is up
	bool IsTimeUp();
	//Return interval of this timer
	Uint32 GetInterval() { return interval; }
	Uint32 GetStartTime() { return startTime; }
private:
	//Holds interval of this timer
	Uint32 interval;
	//Time when this timer was started/restarted
	Uint32 startTime;
};

#endif