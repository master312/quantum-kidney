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
    
    character->SetDirection(0);
    character->SetIsMoving(false);
    
    if(S_IsKeyDown(binds.movement[BIND_MOVE_NORTH])){
        character->PushDirection(PAWN_DIR_NORTH);
        character->SetIsMoving(true);
    }else if(S_IsKeyDown(binds.movement[BIND_MOVE_SOUTH])){
        character->PushDirection(PAWN_DIR_SOUTH);
        character->SetIsMoving(true);
    }
    
    if(S_IsKeyDown(binds.movement[BIND_MOVE_EAST])){
        character->PushDirection(PAWN_DIR_EAST);
        character->SetIsMoving(true);
    }else if(S_IsKeyDown(binds.movement[BIND_MOVE_WEST])){
        character->PushDirection(PAWN_DIR_WEST);
        character->SetIsMoving(true);
    }
}