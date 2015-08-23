/* 
 * File:   cPawn.cpp
 * Author: master312
 * 
 * Created on August 14, 2015, 7:05 PM
 */

#include "cPawn.h"

cPawn::cPawn() {
    animationId = 0;
    animId = 0;
}
cPawn::~cPawn() {
    
}
void cPawn::LoadAnim() {
    char tmp[50];
    sprintf(tmp, "%d.sanim", animationId);
    animId = S_LoadAnimation(tmp);
    if(animId == 0){
        StormPrintLog(STORM_LOG_ERROR, "cPawn", 
                "Could not load animation file '%s'", tmp);
    }
}
void cPawn::Draw() {
    S_DrawAnimation(animId, loc.x, loc.y);
}
//Protected
void cPawn::UnloadAnimation() {
    if(animId > 0)
        S_RemoveAnimation(animId);
}