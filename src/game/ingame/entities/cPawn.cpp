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
void cPawn::Draw(int lookX, int lookY) {
    S_DrawAnimation(animId, (int)loc.x - lookX, (int)loc.y - lookY);
}
//Protected
void cPawn::UnloadAnimation() {
    if(animId > 0)
        S_RemoveAnimation(animId);
}