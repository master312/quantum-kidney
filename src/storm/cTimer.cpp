#include "cTimer.h"

cTimer::cTimer(){
	interval = 1000;
	startTime = 0;
}
cTimer::cTimer(Uint32 _interval){
	interval = _interval;
	startTime = 0;
}
cTimer::~cTimer(){

}
void cTimer::Reset(){
	startTime = SDL_GetTicks();
}
bool cTimer::IsTimeUp(){
	return (SDL_GetTicks() - startTime) >= interval;
}