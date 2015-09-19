#include "cSysAnimation.h"
#include "../cEntity.h"

cSysAnimation::cSysAnimation() {
}
cSysAnimation::~cSysAnimation() {
}
void cSysAnimation::Tick() {
    
}
void cSysAnimation::Draw() {
    for(auto &com : components){
        cComAnimation *cmp = (cComAnimation*)com;
        
        cEntity *tmpE = cmp->GetEntity();
        S_DrawAnimation(cmp->GetAnimId(), tmpE->GetLoc()->x, tmpE->GetLoc()->y);
    }
}