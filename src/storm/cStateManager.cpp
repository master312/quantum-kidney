#include "cStateManager.h"

cStateManager::cStateManager(){
}
cStateManager::~cStateManager(){
	for(int i = 0; i < (int)states.size(); i++){
		while(true){
			cStormState *tmpState = states[i];
			cStormState *lastWithChild = NULL;
			if(tmpState->childState == NULL)
				break;
			while(true){
				if(tmpState->childState != NULL){
					lastWithChild = tmpState;
					tmpState = tmpState->childState;
				}else{
					tmpState->Shutdown();
					delete tmpState;
					lastWithChild->childState = NULL;
					break;
				}
			}
		}
		states[i]->Shutdown();
		delete states[i];
	}
	states.clear();
	StormPrintLog(STORM_LOG_INFO, "cStateManager", "All stated deleted");
}
void cStateManager::PushState(cStormState *curState){
	if(states.size() > 0){
		states[states.size() - 1]->state = STORM_STATE_PAUSED;
		states[states.size() - 1]->Pause();
	}
	curState->Init();
	curState->state = STORM_STATE_INITED;
	states.push_back(curState);
}
void cStateManager::PopState(){
	if(states.size() > 0){
		states[states.size() - 1]->Shutdown();
		delete states[states.size() - 1]; 
		states.pop_back();
		if(states.size() > 0){
			states[states.size() - 1]->state = STORM_STATE_INITED;
			states[states.size() - 1]->Resume();
		}
	}
}
void cStateManager::GraphicsTick(){
	if(states.size() > 0){
		cStormState *tmpState = states[states.size() - 1];
		while(true){
			if(tmpState->childState != NULL){
				tmpState = tmpState->childState;
			}else{
				break;
			}
		}
		if(tmpState->state == STORM_STATE_INITED){
			tmpState->GraphicsTick();
		}
	}
}
void cStateManager::LogicTick(){
	begin:
	if(states.size() > 0){
		cStormState *tmpState = states[states.size() - 1];
		if(tmpState->state == STORM_STATE_END){
			tmpState->Shutdown();
			delete tmpState;
			states.pop_back();
			goto begin;
		}
		if(tmpState->childState != NULL){
			while(true){
				if(tmpState->childState != NULL){
					if(tmpState->childState->state == STORM_STATE_END){
						tmpState->childState->Shutdown();
						delete tmpState->childState;
						tmpState->childState = NULL;
						tmpState->state = STORM_STATE_INITED;
						tmpState->Resume();
					}else{
						tmpState = tmpState->childState;
					}
				}else{
					break;
				}
			}
		}
		if(tmpState->state == STORM_STATE_INITED){
			tmpState->LogicTick();
		}
	}
}

cStormState *cStateManager::GetCurState(){
	if(states.size() > 0)
		return states[states.size() - 1];
	return NULL;
}