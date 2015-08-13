#include "cMusic.h"

cMusic::cMusic(){

}
cMusic::~cMusic(){

}
bool cMusic::Load(std::string _filename){
	StormPrintLog(STORM_LOG_WARNING, "cMusic", "Template class called");
	return false;
}
void cMusic::Play(int _repeat, int fade){
	StormPrintLog(STORM_LOG_WARNING, "cMusic", "Template class called");
}
void cMusic::Stop(int fade){
	StormPrintLog(STORM_LOG_WARNING, "cMusic", "Template class called");
}
void cMusic::Pause(){
	StormPrintLog(STORM_LOG_WARNING, "cMusic", "Template class called");
}
void cMusic::Free(){
	StormPrintLog(STORM_LOG_WARNING, "cMusic", "Template class called");
}