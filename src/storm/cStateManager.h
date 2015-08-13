//Created by Petar Ostojic
//Wed Mar  4 15:30:10 2015
#include "cStormState.h"
#include "fLogs.h"
#include <vector>
#ifndef CSTATEANAGER_H
#define CSTATEANAGER_H
//TODO Someday: This class is not necessary for engine. Can be merged with storm class

class cStateManager{
public:
	cStateManager();
	~cStateManager();

	//Last pushed state will be activated
	void PushState(cStormState *curState);
	//Delete last pushed state; Previously pushed state will be activated, if any
	//State object will also be deleted from memory
	void PopState();

	void GraphicsTick();
	void LogicTick();

	//Returns currently active state
	cStormState *GetCurState();
private:
	std::vector<cStormState*> states;
};

#endif