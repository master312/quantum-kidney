/* 
 * File:   cComImage.h
 * Author: master312
 *
 * Created on September 15, 2015, 9:23 PM
 */

#ifndef CCOMIMAGE_H
#define	CCOMIMAGE_H
#include "cComponent.h"

class cComImage : public cComponent {
public:
    cComImage(luabridge::LuaRef &table);
    ~cComImage();
    
    int Init();
    
    bool IsInited() { return isInited; }
    bool IsCropped() { return cropRect != nullptr; }
    
    uint GetTextureId() { return textureId; }
    void SetTextureId(uint _id) { textureId = _id; }
private:
    std::string imgFilename;
    uint textureId;
    sRect *cropRect;
    
    bool isInited;
};

#endif	/* CCOMIMAGE_H */

