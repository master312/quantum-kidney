//Created by Petar Ostojic;
//Mon June 27 02:47:18 2015
//This class manages all events, and calls event handlers
#include "cInput.h"
#include "cInputSDL2.h"
#include "../cStormCallbacker.h"
#include "../graphics/cGraphics.h"
#include "../fLogs.h"
#include <map>
#ifndef CEVENTMANAGER_H
#define CEVENTMANAGER_H
//TODO: Event eat logging
//TODO: Handler callback priority;
//TODO: Handler ignore option
//TODO: Better event eating
//	--Figure it out
class cEventManager {
public:
	cEventManager(int _api, cGraphics *_graph);
	~cEventManager();

	//Adds new event handler function
	void AddHandler(cStormCallbacker *_callback, std::string _name);
	//Removes event handler from manager
	void RemoveHandler(std::string _name);
	//Clears all event handlers
	void Clear();

	void Tick();

	//Eats current event. No event handlers after this one will be called
	//@name is name of event handler that eaten event
	void Eat(std::string _name);

	//Is quit signal received ?
	bool ToQuit() { return mInput->ToQuit(); }
	//Returns pointer to input manager
	cInput *GetInputManager() { return mInput; }
private:
	//Pointer to input manager
	cInput *mInput;
	std::map<std::string, cStormCallbacker*> handlers;
	//Weather last event was eaten
	bool isEat;
};

#endif