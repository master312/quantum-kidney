//Created by Petar Ostojic
//Wed Mar  4 15:15:26 2015
//This is template class for game state class. Its only used for extending other classes
#include "defines.h"
#ifndef CSTORMSTATE_H
#define CSTORMSTATE_H

class cStormState{
public:
	cStormState *childState;
	//Current state of this state class :); Can be created, inited, paused, or ended
	int state;
	//True if this state have parent
	bool haveParent;

	cStormState();
	virtual ~cStormState(){}

	//Called when class is initialized
	virtual void Init() = 0;
	//Called when graphics is ticked
	virtual void GraphicsTick() { }
	//Called when logic is ticked
	virtual void LogicTick() = 0;
	//Called when state has been paused
	virtual void Pause()  { }
	//Called on state resume
	virtual void Resume()  { }
	//Called when this state has been ended
	virtual void Shutdown() = 0;

	//Push new state (to child state); This state will be paused, until child state is finished
	//Every state can have ONLY one child state
	void PushState(cStormState *_state);
	//Clears child state
	//Id toDelete is true, child state object will be deleted from memory; Default is false
	//Warning! Don't forget to manually delete state class, if toDelete is false
	void PopState(bool toDelete = false);
	//This function will end state
	void End();
};

#endif