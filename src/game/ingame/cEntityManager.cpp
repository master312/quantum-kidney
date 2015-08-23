/* 
 * File:   cEntityManager.cpp
 * Author: master312
 * 
 * Created on August 23, 2015, 12:31 AM
 */

#include "cEntityManager.h"

cEntityManager::cEntityManager() {
}
cEntityManager::~cEntityManager() {
}
void cEntityManager::Tick() {
    for(int i = 0; i < (int)entities.size(); i++){
        cEntity *tmpE = entities[i];
        if(tmpE->IsPawn()){
            HandlePawn((cPawn*)tmpE);
        }else if(tmpE->IsObject()){
            
        }
    }
}
void cEntityManager::PushEntity(cEntity *e){
    entities.push_back(e);
}
//Private methods
void cEntityManager::HandlePawn(cPawn *pawn) {
    //Handle pawn's movement
    if(!pawn->IsMoving())
        return;
    int sp = pawn->GetStats()->speed;
    switch(pawn->GetDirection()){
        case PAWN_DIR_NORTH:
            pawn->GetLoc()->y -= sp;
            break;
        case PAWN_DIR_EAST:
            pawn->GetLoc()->x += sp;
            break;
        case PAWN_DIR_SOUTH:
            pawn->GetLoc()->y += sp;
            break;
        case PAWN_DIR_WEST:
            pawn->GetLoc()->x -= sp;
            break;
    }
}