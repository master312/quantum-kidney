#include "cCameraManager.h"

cCameraManager::cCameraManager() {
}
cCameraManager::~cCameraManager() {    
}
void cCameraManager::Tick(){
    sCommon *tmpC = GetCommon();
    cVector2d *tmp = tmpC->playerDriver->GetCharacter()->GetLoc();
    tmpC->mapManager->HandleCamera((int)tmp->x, (int)tmp->y);
}

