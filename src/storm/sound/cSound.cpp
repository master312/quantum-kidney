#include "cSound.h"

cSound::cSound(){
	filename = "";
}
cSound::~cSound(){
}
bool cSound::Load(std::string _filename){
	StormPrintLog(STORM_LOG_WARNING, "cSound", "Template class called");
	return false;
}
void cSound::Play(int _repeat){
	StormPrintLog(STORM_LOG_WARNING, "cSound", "Template class called");
}
void cSound::Pause(){
	StormPrintLog(STORM_LOG_WARNING, "cSound", "Template class called");
}
void cSound::Stop(){
	StormPrintLog(STORM_LOG_WARNING, "cSound", "Template class called");
}
void cSound::Free(){
	StormPrintLog(STORM_LOG_WARNING, "cSound", "Template class called");
}