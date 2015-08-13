//Created by Petar Ostojic;
//Mon June 27 02:04:11 2015
//This class handles function callback on timer
#include "cStormCallbacker.h"
#include "defines.h"
#include <map>
#ifndef CTIMEDCALLBACKMANAGER_H
#define CTIMEDCALLBACKMANAGER_H

class cTimedCallbackManager {
public:
	cTimedCallbackManager();
	~cTimedCallbackManager();

	//Adds new functions to manager
	//WARNING: Minimal callback interval 
	//is defined in defines.h -STORM_TIMED_CALLBACK_INTERVAL
	uint Add(cStormCallbacker *_cb);
	//Removes function from callback manager
	//This function will also delete cStormCallbacker* object
	void Remove(uint id);
	//Removes all functions from manager
	void ClearAll();

	void Tick();

	//Returns pointer to cStormCallbacker, matching @id
	//Returns NULL if not found
	cStormCallbacker *Get(uint id);
private:
	std::map<uint, cStormCallbacker*> cb;
	Uint32 lastTick;
};

#endif