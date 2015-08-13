#include "cStMainMenu.h"

cStMainMenu::cStMainMenu(){
	
}
cStMainMenu::~cStMainMenu(){
	
}
void cStMainMenu::Init(){
    S_AddEventHandler(
            new cStormCallbacker(this, &cStMainMenu::HandleEvents), 
            "cStMainMenu");

    StormPrintLog(STORM_LOG_INFO, "cStMainMenu", "State initialized");
}
void cStMainMenu::GraphicsTick(){
    S_RenderText("State: cStMainMenu", 1, 1);
    S_RenderText("Zulfirova igra sine \n Cuknide enter to continue", 5, 60);
}
void cStMainMenu::LogicTick(){
	
}
void cStMainMenu::HandleEvents(){
    if(S_IsKeyDown(KEY_RETURN)){
        PushState(new cStInGame());
    } else if(S_IsKeyDown(KEY_ESCAPE)){
        S_Quit();
    }
}
void cStMainMenu::Pause(){
    StormPrintLog(STORM_LOG_INFO, "cMainMenu", "State paused");
    S_RemoveEventHandler("cStMainMenu");
}
void cStMainMenu::Resume(){
    S_AddEventHandler(
            new cStormCallbacker(this, &cStMainMenu::HandleEvents),
            "cStMainMenu");

    StormPrintLog(STORM_LOG_INFO, "cMainMenu", "State resumed");
}
void cStMainMenu::Shutdown(){
    StormPrintLog(STORM_LOG_INFO, "cMainMenu", "State ended");
}