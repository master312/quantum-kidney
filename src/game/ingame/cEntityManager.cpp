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
void cEntityManager::Draw() {
    sPoint *cam = GetCommon()->mapManager->GetCamera();
    
    for(int i = 0; i < (int)entities.size(); i++){
        cEntity *tmpE = entities[i];
        if(tmpE->IsPawn()){
            ((cPawn*)tmpE)->Draw(cam->x, cam->y);
        }
    }
}
void cEntityManager::PushEntity(cEntity *e){
    entities.push_back(e);
}
//Private methods
void cEntityManager::HandlePawn(cPawn *pawn) {
    //Handle pawn's movement
    cAnimation *anim = pawn->GetAnimation();
    
    if(!pawn->IsMoving()){
        if(!anim->IsPaused()){
            anim->Pause();
            anim->Reset();
        }
        return;
    }
    if(anim->IsPaused())
        anim->Resume();
    
    int delta = S_GetDelta();
    
    float sp = (float)pawn->GetStats()->speed / 1000;
    switch(pawn->GetDirection()){
        case PAWN_DIR_NORTH:
            pawn->GetLoc()->y -= (sp * delta);
            anim->SetFrameGroup("walk_n");
            break;
        case PAWN_DIR_EAST:
            pawn->GetLoc()->x += (sp * delta);
            anim->SetFrameGroup("walk_e");
            break;
        case PAWN_DIR_SOUTH:
            pawn->GetLoc()->y += (sp * delta);
            anim->SetFrameGroup("walk_s");
            break;
        case PAWN_DIR_WEST:
            pawn->GetLoc()->x -= (sp * delta);
            anim->SetFrameGroup("walk_w");
            break;
    }
}