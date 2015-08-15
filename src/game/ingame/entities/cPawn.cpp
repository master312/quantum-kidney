/* 
 * File:   cPawn.cpp
 * Author: master312
 * 
 * Created on August 14, 2015, 7:05 PM
 */

#include "cPawn.h"

cPawn::cPawn() {
    spriteId = 0;
    spriteTexture = 0;
    animationId = 0;
    animId = 0;
}
cPawn::~cPawn() {
    
}
void cPawn::LoadSprite() {
    
}
void cPawn::Draw() {
    
}
//Protected
void cPawn::UnloadSprites() {
    if(spriteTexture > 0)
        S_UnloadTexture(spriteTexture);
    if(animId > 0)
        S_RemoveAnimation(animId);
}