#include "cMusicSDL2.h"

cMusicSDL2::cMusicSDL2(){
	music = NULL;
	isPaused = false;
}
cMusicSDL2::~cMusicSDL2(){

}

bool cMusicSDL2::Load(std::string _filename){
	filename = _filename;
	std::string fullPath = (char*)STORM_DIR_MUSIC + filename; 
	music = Mix_LoadMUS(fullPath.c_str());
	if(music == NULL){
		StormPrintLog(STORM_LOG_ERROR, "cMusicSDL2", 
				"Could not load music file: ", fullPath.c_str());
		return false;
	}
	return true;
}
void cMusicSDL2::Play(int _repeat, int fade){
	if(music != NULL){
		if(Mix_PlayingMusic() > 0){	//Music is already playing
			if(isPaused){
				Mix_ResumeMusic();
				isPaused = false;
				return;
			}else if(Mix_FadingMusic() == MIX_FADING_OUT){
				Mix_HaltMusic();
			}else{
				return;
			}
		}
		if(Mix_FadeInMusic(music, _repeat, fade) < 0){
			StormPrintLog(STORM_LOG_ERROR, "cMusicSDL2", "Error %s", Mix_GetError());
		}
	}
}
void cMusicSDL2::Stop(int fade){
	Mix_FadeOutMusic(fade);
}
void cMusicSDL2::Pause(){
	Mix_PauseMusic();
	isPaused = true;
}
void cMusicSDL2::Free(){
	if(music != NULL){
		Mix_FreeMusic(music);
	}
}