/* 
 * File:   cCommon.h
 * Author: master312
 *
 * Created on August 13, 2015, 9:21 PM
 */

#ifndef CCOMMON_H
#define	CCOMMON_H
#include <iostream>

class cMapManager;
class cEntityManager;
class cCameraManager;
class cPlayerDriver;

struct sCommon {
    sCommon();
    ~sCommon();

    /* Map tile size in pixels */
    int mapTileWidth, mapTileHeight;
    /* Map layer count limit */
    int mapMaxBot, mapMaxTop;
    /* Size of one map chunk (in tiles) */
    int mapChunkWidth, mapChunkHeight;
    /* Size of map chunk in pixels */
    int mapChunkWidthPx, mapChunkHeightPx;
    /* World size in map chunks */
    int mapWorldWidth, mapWorldHeight;
    /* Delete map chunk from memory if unused for this amount of time ( ms ) */
    int mapChunkTimeout;
    
    cMapManager *mapManager;
    cPlayerDriver *playerDriver;
    cEntityManager *entityManager;
    cCameraManager *cameraManager;
};

sCommon *GetCommon();
void DeleteCommon();

#endif	/* CCOMMON_H */

