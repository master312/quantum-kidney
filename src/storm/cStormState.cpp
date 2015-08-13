#include "cStormState.h"

cStormState::cStormState(){
	childState = NULL;
	state = STORM_STATE_CREATED;
	haveParent = false;
}
void cStormState::PushState(cStormState *_state){
	state = STORM_STATE_PAUSED;
	childState = _state;
	if(childState->state == STORM_STATE_CREATED){
		childState->Init();
		childState->state = STORM_STATE_INITED;
		childState->haveParent = true;
		Pause();
	}
}
void cStormState::PopState(bool toDelete){
	if(childState != NULL){
		if(toDelete){
			childState->Shutdown();
			delete childState;
		}
		childState = NULL;
		Resume();
	}
}
void cStormState::End(){
	state = STORM_STATE_END;
}