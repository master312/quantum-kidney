#include "cSysPlayerDriver.h"
#include "../cEntity.h"

cSysPlayerDriver::cSysPlayerDriver() {
    S_AddEventHandler(
                new cStormCallbacker(this, &cSysPlayerDriver::HandleEvents), 
                "cSysPlayerDriver");

}
cSysPlayerDriver::~cSysPlayerDriver() {
}
void cSysPlayerDriver::HandleEvents(void* data) {
    for(auto &c : components){
        cComPawn *comP = c->GetEntity()->GetComponent<cComPawn>();
        if(comP != nullptr){
            HandleEvent(comP);        
        }
    }
}
void cSysPlayerDriver::Tick() {
    for(auto &c : components){
        cComPawn *com = c->GetEntity()->GetComponent<cComPawn>();
        if(com != nullptr && com->IsMoving()){
            com->Move();
        }
    }    
}
//Private methods
void cSysPlayerDriver::HandleEvent(cComPawn *comP) {
    short tmpDir = 0;
    if(S_IsKeyDown(KEY_UP)){
        tmpDir = COM_DIR_N;
    }else if(S_IsKeyDown(KEY_DOWN)){
        tmpDir = COM_DIR_S;
    }
    if(S_IsKeyDown(KEY_LEFT)){
        if(tmpDir == COM_DIR_N){
            tmpDir = COM_DIR_NW;
        }else if(tmpDir == COM_DIR_S){
            tmpDir = COM_DIR_SW;
        }else{
            tmpDir = COM_DIR_W;
        }
    }else if(S_IsKeyDown(KEY_RIGHT)){
        if(tmpDir == COM_DIR_N){
            tmpDir = COM_DIR_NE;
        }else if(tmpDir == COM_DIR_S){
            tmpDir = COM_DIR_SE;
        }else{
            tmpDir = COM_DIR_E;
        }
    }
    if(tmpDir != 0){    //TODO: Optimize
        comP->SetDir(tmpDir);
        comP->SetIsMoving(true);
    }else{
        comP->SetIsMoving(false);
    }
}

