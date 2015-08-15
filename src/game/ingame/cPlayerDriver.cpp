/* 
 * File:   cPlayerDriver.cpp
 * Author: master312
 * 
 * Created on August 15, 2015, 3:14 AM
 */

#include "cPlayerDriver.h"

cPlayerDriver::cPlayerDriver() {
    character = NULL;
}
cPlayerDriver::~cPlayerDriver() {
}
void cPlayerDriver::Init() {
    S_AddEventHandler(
            new cStormCallbacker(this, &cPlayerDriver::HandleEvents), 
            "cPlayerDriver");
    
    StormPrintLog(STORM_LOG_INFO, "cPlayerDriver", "Initialized");
}
void cPlayerDriver::HandleEvents() {
    if(character == NULL)
        return;
    
    int speed = character->GetStats()->speed;
    if(S_IsKeyDown(binds.movement[BIND_MOVE_UP])){
        character->GetLoc()->y -= speed;
    }else if(S_IsKeyDown(binds.movement[BIND_MOVE_DOWN])){
        character->GetLoc()->y += speed;
    }
    
    if(S_IsKeyDown(binds.movement[BIND_MOVE_RIGHT])){
        character->GetLoc()->x += speed;
    }else if(S_IsKeyDown(binds.movement[BIND_MOVE_LEFT])){
        character->GetLoc()->x -= speed;
    }
}