#include "cComImage.h"

cComImage::cComImage(luabridge::LuaRef &table) {
    isInited = false;
    cropRect = nullptr;
    
    luabridge::LuaRef tmpReff = table["file_name"];
    if(tmpReff.isNil() || !tmpReff.isString()){
        StormPrintLog(STORM_LOG_ERROR, "cComImage", 
                "Could not create Com_Image. Filename invalid");
        return;
    }
    imgFilename = tmpReff.cast<std::string>();
    
    tmpReff = table["crop_rectangle"];
    if(!tmpReff.isNil()){
        //Source rect is specified
        if(!tmpReff.isTable()){
            StormPrintLog(STORM_LOG_WARNING, "cComImage", 
                "Skipping 'source_rectangle' element. Structure error");
        } else {
            if(!tmpReff["width"].isNil() && tmpReff["width"].isNumber() && 
               !tmpReff["height"].isNil() && tmpReff["height"].isNumber()) {
                //Width and height are specified in 'source_rectangle' element
                cropRect = new sRect();
                cropRect->w = tmpReff["width"].cast<int>();
                cropRect->h = tmpReff["height"].cast<int>();
            }
            if(!tmpReff["x"].isNil() && tmpReff["x"].isNumber() && 
               !tmpReff["y"].isNil() && tmpReff["y"].isNumber()) {
                //Width and height are specified in 'source_rectangle' element
                if(cropRect == nullptr){
                    cropRect = new sRect();
                }
                cropRect->x = tmpReff["x"].cast<int>();
                cropRect->y = tmpReff["y"].cast<int>();
            }
        }
    }
    
}
cComImage::~cComImage() {
    if(cropRect == nullptr){
        S_UnloadTexture(textureId);
    }else{
        sTextureSection *sec = S_GetSection(textureId);
        S_UnloadTexture(sec->texture);
        S_RemoveSection(textureId);
        delete cropRect;
    }
}
int cComImage::Init() {
    textureId = S_LoadTexture(imgFilename);
    if(cropRect != nullptr){
        //Image is cropped
        textureId = S_CreateSection(textureId, *cropRect);
    }
    
    imgFilename.clear();
}
