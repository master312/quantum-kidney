#include "cEventManager.h"

cEventManager::cEventManager(int _api, cGraphics *_graph){
	mInput = new cInputSDL2();
	mInput->SetGraphics(_graph);
	isEat = false;

	StormPrintLog(STORM_LOG_INFO, "cEventManager", 
			"Event manager initialized");
}
cEventManager::~cEventManager(){
	delete mInput;
}
void cEventManager::AddHandler(cStormCallbacker *_callback, std::string _name){
	if(handlers.count(_name) > 0){
		StormPrintLog(STORM_LOG_ERROR, "cEventManager", 
			"Event handler with name '%s' already exists!", _name.c_str());
		return;
	}
	handlers[_name] = _callback;
	
	StormPrintLog(STORM_LOG_INFO, "cEventManager", 
		"New event handler '%s' has been added to manager", _name.c_str());
}
void cEventManager::RemoveHandler(std::string _name){
	if(handlers.count(_name) == 0)
		return;
	delete handlers[_name];
	handlers.erase(_name);
	
	StormPrintLog(STORM_LOG_INFO, "cEventManager", 
		"Event handler '%s' has been removed from manager", _name.c_str());
}
void cEventManager::Clear(){
	std::map<std::string, cStormCallbacker*>::iterator it;
	for(it = handlers.begin(); it != handlers.end(); ++it){
		delete it->second;
	}
	handlers.clear();
}
void cEventManager::Tick(){
	while(mInput->Update()){
		std::map<std::string, cStormCallbacker*>::iterator it;
		for(it = handlers.begin(); it != handlers.end(); ++it){
			it->second->Call();
			if(isEat){
				//Event was eaten by current handler
				isEat = false;
				break;
			}
		}
	}
}

void cEventManager::Eat(std::string _name){
	isEat = true;
}