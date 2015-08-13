#include "cTimedCallbackManager.h"

cTimedCallbackManager::cTimedCallbackManager(){
	lastTick = 0;
}
cTimedCallbackManager::~cTimedCallbackManager(){
	ClearAll();
}

uint cTimedCallbackManager::Add(cStormCallbacker *_cb){
	uint toReturn;
	if(cb.size() > 0){
		std::map<uint, cStormCallbacker*>::iterator i = cb.end();
		--i;
		cb[i->first + 1] = _cb;
		toReturn = i->first + 1;
	}else{
		cb[1] = _cb;
		toReturn = 1;
	}
	return toReturn;
}
void cTimedCallbackManager::Remove(uint id){
	if(cb.count(id) <= 0){
		return;
	}
	delete cb[id];
	cb.erase(id);
}
void cTimedCallbackManager::ClearAll(){
	std::map<uint, cStormCallbacker*>::iterator i;
	for(i = cb.begin(); i != cb.end(); ++i){
		delete i->second;
	}
	cb.clear();
}	

void cTimedCallbackManager::Tick(){
	if(SDL_GetTicks() - lastTick < STORM_TIMED_CALLBACK_INTERVAL){
		return;
	}
	lastTick = SDL_GetTicks();

	std::map<uint, cStormCallbacker*>::iterator i;
	for(i = cb.begin(); i != cb.end(); ++i){
		if(lastTick - i->second->GetLastTick() < (Uint32)i->second->GetInterval()){
			continue;
		}
		i->second->Call();
		i->second->SetLastTick(lastTick);
	}
}

cStormCallbacker *cTimedCallbackManager::Get(uint id){
	if(cb.count(id) <= 0){
		return NULL;
	}
	return cb[id];
}