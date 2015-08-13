#include "cAnimation.h"

cAnimation::cAnimation(){
	lastTick = SDL_GetTicks();
	fps = 1;
	firstFrame = lastFrame = curFrame = 0;
	isPaused = false;
	repetations = -1;
	isDone = false;
	isFile = false;
	filename = "";
}
cAnimation::~cAnimation(){

}
void cAnimation::Update(){
	if(isDone || isPaused || textures.size() == 0){
		return;
	}
	if((uint)((float)1000/fps) < (SDL_GetTicks() - lastTick)){
		curFrame ++;
		lastTick = SDL_GetTicks();
		if(curFrame >= lastFrame){
			if(repetations != -1){
				if(repetations == 0){
					isPaused = true;
					isDone = true;
				}else{
					repetations--;
				}
			}
			curFrame = firstFrame;	//Reset animation to first frame
		}
	}
}
void cAnimation::SetTexture(uint _texture, int frame){
	textures[frame] = _texture;
}