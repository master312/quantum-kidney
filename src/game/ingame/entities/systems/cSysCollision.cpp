#include "cSysCollision.h"

cSysCollision::cSysCollision() {
    debugDraw = false;
    S_ConsoleAddHandler("debug_collision", 
                        cStormCallbacker(this, &cSysCollision::HandleCmd));
}
cSysCollision::~cSysCollision() {
}
void cSysCollision::Tick() {
    for(auto &c : components){
        cComCollision *com = (cComCollision*)c;
        
        for(auto &c2 : components){
            cComCollision *com2 = (cComCollision*)c2;
            if(com->GetEntity() == com2->GetEntity())
                continue;
            
            if(com->GetCollider().IsCollision(&com2->GetCollider())){
                com->HandleCollision(com2);
                com2->HandleCollision(com);
            }
        }        
    }
}
void cSysCollision::Draw() {
    if(!debugDraw)
        return;
    
    for(auto &c : components){
        cComCollision *com = (cComCollision*)c;
        S_DrawFillRect(&com->GetCollider());
    }
}
void cSysCollision::HandleCmd(void *data) {
    char **tmp = (char**)data;
    if(tmp[1] == NULL){
        S_ConsolePrintLine("Command must be in format 'debug_collision 1/0'");
        return;
    }
    debugDraw = tmp[1][0] == '1';
}