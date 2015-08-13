/* 
 * File:   cCommon.cpp
 * Author: master312
 * 
 * Created on August 13, 2015, 9:21 PM
 */

#include "sCommon.h"

sCommon *pubCommon = NULL;

sCommon::sCommon() {
    tileWidth = tileHeight = 32;
    mapMaxBot = 3;
    mapMaxTop = 2;
    mapChunkWidth = mapChunkHeight = 50;
    mapChunkWidthPx = mapChunkWidth * tileWidth;
    mapChunkHeightPx = mapChunkHeight * tileHeight;
    mapChunkTimeout = 5000;
}

sCommon::~sCommon() {
}

sCommon *GetCommon() {
    if(pubCommon == NULL)
        pubCommon = new sCommon();
    return pubCommon;
}
void DeleteCommon() {
    delete pubCommon;
}
