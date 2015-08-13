#include "cSoundManagerSDL2.h"

cSoundManagerSDL2::cSoundManagerSDL2(){

}
cSoundManagerSDL2::~cSoundManagerSDL2(){

}
bool cSoundManagerSDL2::Initialize(int frenquency){
	if(Mix_Init(MIX_INIT_MP3 | MIX_INIT_FLAC) < 0){
		StormPrintLog(STORM_LOG_ERROR, "cSoundManagerSDL2", "Could not initialize SDL mixer");
		return false;
	}
	if(Mix_OpenAudio(frenquency, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
		StormPrintLog(STORM_LOG_ERROR, "cSoundManagerSDL2", "Could not open sound channel");
		return false;
	}
	isMusicPaused = false;
	StormPrintLog(STORM_LOG_INFO, "cSoundManagerSDL2", "Sound system initialized");
	return true;
}
void cSoundManagerSDL2::Shutdown(){
	DeleteAllSounds();
	DeleteAllMusic();
	Mix_Quit();
}
uint cSoundManagerSDL2::LoadSound(std::string filename){
	uint toReturn = 0;
	cSoundSDL2 *tmpS = new cSoundSDL2();
	if(!tmpS->Load(filename))
		return toReturn;

	if(sounds.size() > 0){
		std::map<uint, cSoundSDL2*>::iterator i = sounds.end();
		--i;
		sounds[i->first + 1] = tmpS;
		toReturn = i->first + 1;
	}else{
		sounds[1] = tmpS;
		toReturn = 1;
	}

	StormPrintLog(STORM_LOG_INFO, "cSoundManagerSDL2", "Sound %s loaded", filename.c_str());
	return toReturn;
}
void cSoundManagerSDL2::DeleteSound(uint soundId){
	if(sounds.count(soundId) > 0){
		sounds[soundId]->Free();
		delete sounds[soundId];
		sounds.erase(soundId);
	}else{
		StormPrintLog(STORM_LOG_WARNING, "cSoundManagerSDL2", 
			"Tried to unload non-existing sound");
	}
}
void cSoundManagerSDL2::DeleteAllSounds(){
	std::map<uint, cSoundSDL2*>::iterator i;
	for(i = sounds.begin(); i != sounds.end(); ++i){
		i->second->Free();
		delete i->second;
	}
	sounds.clear();
	StormPrintLog(STORM_LOG_INFO, "cSoundManagerSDL2", "All sounds unloaded");
}
void cSoundManagerSDL2::SetSoundVolume(int volume){
	if(volume > 128)
		volume = 128;
	if(volume < 0)
		volume = 0;
	soundVolume = volume;
	Mix_Volume(-1, soundVolume);
}
void cSoundManagerSDL2::PlaySound(uint soundId, int _repeat){
	if(sounds.count(soundId) > 0){
		sounds[soundId]->Play(_repeat);
	}
}
void cSoundManagerSDL2::StopSound(uint soundId){
	if(sounds.count(soundId) > 0){
		sounds[soundId]->Stop();
	}
}
cSound *cSoundManagerSDL2::GetSound(uint soundId){
	if(sounds.count(soundId) > 0){
		return sounds[soundId];
	}
	return NULL;
}
uint cSoundManagerSDL2::LoadMusic(std::string filename){
	uint toReturn = 0;
	cMusicSDL2 *tmpM = new cMusicSDL2();
	if(!tmpM->Load(filename))
		return toReturn;

	if(musics.size() > 0){
		std::map<uint, cMusicSDL2*>::iterator i = musics.end();
		--i;
		musics[i->first + 1] = tmpM;
		toReturn = i->first + 1;
	}else{
		musics[1] = tmpM;
		toReturn = 1;
	}
	StormPrintLog(STORM_LOG_INFO, "cSoundManagerSDL2", "Music %s loaded", filename.c_str());
	return toReturn;
}
void cSoundManagerSDL2::DeleteMusic(uint musicId){
	if(musics.count(musicId) > 0){
		musics[musicId]->Free();
		delete musics[musicId];
		musics.erase(musicId);
	}else{
		StormPrintLog(STORM_LOG_WARNING, "cSoundManagerSDL2", 
			"Tried to unload non-existing music");
	}
}
void cSoundManagerSDL2::DeleteAllMusic(){
	std::map<uint, cMusicSDL2*>::iterator i;
	for(i = musics.begin(); i != musics.end(); ++i){
		i->second->Free();
		delete i->second;
	}
	musics.clear();
	StormPrintLog(STORM_LOG_INFO, "cSoundManagerSDL2", "All music unloaded");
}
void cSoundManagerSDL2::StopMusic(){
	if(musicPlaying != 0 && musics.count(musicPlaying) > 0){
		musics[musicPlaying]->Stop(DEFAULT_FADE_TIME);
	}
	musicPlaying = 0;
}
void cSoundManagerSDL2::PauseMusic(){
	if(musicPlaying != 0 && musics.count(musicPlaying) > 0){
		musics[musicPlaying]->Pause();
		isMusicPaused = true;
	}
}
void cSoundManagerSDL2::ResumeMusic(){
	if(musicPlaying != 0 && musics.count(musicPlaying) > 0 && isMusicPaused){
		musics[musicPlaying]->Play();
	}
}
void cSoundManagerSDL2::SetMusicVolume(int volume){
	if(volume > 128)
		volume = 128;
	if(volume < 0)
		volume = 0;
	musicVolume = volume;
	Mix_VolumeMusic(musicVolume);
}
void cSoundManagerSDL2::PlayMusic(uint musicId, int _repeat){
	if(musics.count(musicId) > 0){
		if(isMusicPaused){
			if(musicId != musicPlaying){
				Mix_HaltMusic();
			}else{
				return;
			}
		}
		if(musicId == musicPlaying && !isMusicPaused)
			return;
		if(musicPlaying != 0){
			Mix_HaltMusic();
		}
		musics[musicId]->Play(_repeat, DEFAULT_FADE_TIME);
		musicPlaying = musicId;
	}
}
bool cSoundManagerSDL2::IsMusicPlaying(){
	return musicPlaying != 0;
}
cMusic *cSoundManagerSDL2::GetMusic(uint musicId){
	if(musics.count(musicId) > 0){
		return musics[musicId];
	}
	return NULL;
}