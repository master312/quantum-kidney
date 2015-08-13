#include "cSoundManager.h"

cSoundManager::cSoundManager(){
	soundVolume = musicVolume = 0;
	musicPlaying = 0;
}
cSoundManager::~cSoundManager(){
}

bool cSoundManager::Initialize(int frenquency){
	StormPrintLog(STORM_LOG_ERROR, "cSoundManager", "Template class called");
	return false;
}
void cSoundManager::Shutdown(){
	StormPrintLog(STORM_LOG_ERROR, "cSoundManager", "Template class called");
}
uint cSoundManager::LoadSound(std::string filename){
	StormPrintLog(STORM_LOG_ERROR, "cSoundManager", "Template class called");
	return 0;
}
void cSoundManager::DeleteSound(uint soundId){
	StormPrintLog(STORM_LOG_ERROR, "cSoundManager", "Template class called");
}
void cSoundManager::DeleteAllSounds(){
	StormPrintLog(STORM_LOG_ERROR, "cSoundManager", "Template class called");
}
void cSoundManager::SetSoundVolume(int volume){
	StormPrintLog(STORM_LOG_ERROR, "cSoundManager", "Template class called");
}
void cSoundManager::PlaySound(uint soundId, int _repeat){
	StormPrintLog(STORM_LOG_ERROR, "cSoundManager", "Template class called");
}
void cSoundManager::StopSound(uint soundId){
	StormPrintLog(STORM_LOG_ERROR, "cSoundManager", "Template class called");
}
cSound *cSoundManager::GetSound(uint soundId){
	StormPrintLog(STORM_LOG_ERROR, "cSoundManager", "Template class called");
	return NULL;
}
uint cSoundManager::LoadMusic(std::string filename){
	StormPrintLog(STORM_LOG_ERROR, "cSoundManager", "Template class called");
	return 0;
}
void cSoundManager::DeleteMusic(uint musicId){
	StormPrintLog(STORM_LOG_ERROR, "cSoundManager", "Template class called");
}
void cSoundManager::DeleteAllMusic(){
	StormPrintLog(STORM_LOG_ERROR, "cSoundManager", "Template class called");
}
void cSoundManager::StopMusic(){
	StormPrintLog(STORM_LOG_ERROR, "cSoundManager", "Template class called");
}
void cSoundManager::PauseMusic(){
	StormPrintLog(STORM_LOG_ERROR, "cSoundManager", "Template class called");
}
void cSoundManager::ResumeMusic(){
	StormPrintLog(STORM_LOG_ERROR, "cSoundManager", "Template class called");
}
void cSoundManager::SetMusicVolume(int volume){
	StormPrintLog(STORM_LOG_ERROR, "cSoundManager", "Template class called");
}
void cSoundManager::PlayMusic(uint musicId, int _repeat){
	StormPrintLog(STORM_LOG_ERROR, "cSoundManager", "Template class called");
}
bool cSoundManager::IsMusicPlaying(){
	StormPrintLog(STORM_LOG_ERROR, "cSoundManager", "Template class called");
	return false;
}
cMusic *cSoundManager::GetMusic(uint musicId){
	StormPrintLog(STORM_LOG_ERROR, "cSoundManager", "Template class called");
	return NULL;
}