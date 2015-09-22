#include "cSysImage.h"
#include "../cEntity.h"

cSysImage::cSysImage() {
}
cSysImage::~cSysImage() {
}
void cSysImage::Draw() {
    for(auto &c : components){
        cComImage *com = (cComImage*)c;
        cVector2d *loc = com->GetEntity()->GetLoc();
        
        if(com->IsCropped()){
            S_DrawSection(com->GetTextureId(), loc->x, loc->y);
        }else{
            S_DrawTexture(com->GetTextureId(), loc->x, loc->y);    
        }
    }
}