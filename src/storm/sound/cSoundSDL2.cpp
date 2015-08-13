#include "cSoundSDL2.h"

cSoundSDL2::cSoundSDL2(){
	sound = NULL;
	channel = -1;
}
cSoundSDL2::~cSoundSDL2(){

}

bool cSoundSDL2::Load(std::string _filename){
	filename = _filename;
	std::string fullPath = (char*)STORM_DIR_SOUND + filename;
	sound = Mix_LoadWAV(fullPath.c_str());
	if(sound == NULL){
		StormPrintLog(STORM_LOG_ERROR, "cSoundSDL2", 
				"Could not load sound file %s", fullPath.c_str());
		return false;
	}
	StormPrintLog(STORM_LOG_INFO, "cSoundSDL2", "Sound file %s loaded", fullPath.c_str());
	return true;
}
void cSoundSDL2::Play(int _repeat){
	if(channel > -1){
		if(Mix_Playing(channel) > 0){		//Channel is playing
			if(Mix_Paused(channel) == 0){	//Channel is not paused
				return;
			}else{		//Channel is paused
				Mix_Resume(channel);
				return;
			}
		}
		channel = -1;
	}
	if(_repeat > 0){
		_repeat -= 1;
	}
	channel = Mix_PlayChannel(-1, sound, _repeat);
	if(channel == -1) {
		StormPrintLog(STORM_LOG_ERROR, "cSoundSDL2", "Error: %s", Mix_GetError());
	}
}
void cSoundSDL2::Pause(){
	if(channel > -1){
		Mix_Pause(channel);
	}
}
void cSoundSDL2::Stop(){
	if(channel > -1){
		Mix_HaltChannel(channel);
		channel = -1;
	}
}
void cSoundSDL2::Free(){
	if(sound != NULL){
		Mix_FreeChunk(sound);
	}
}