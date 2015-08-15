/* 
 * File:   cMapManager.cpp
 * Author: master312
 * 
 * Created on August 14, 2015, 5:29 PM
 */

#include "cMapManager.h"

cMapManager::cMapManager() {
}
cMapManager::~cMapManager() {
}
void cMapManager::Init() {
    for(int i = 0; i < GetCommon()->mapWorldWidth; i++){
        std::vector<cMapChunk*> tmpVec;
        
        for(int j = 0; j < GetCommon()->mapWorldHeight; j++){
            tmpVec.push_back(NULL);
        }
        
        chunks.push_back(tmpVec);
        tmpVec.clear();
    }
    
    S_AddTimedCallback(
                new cStormCallbacker(this, 
                                    &cMapManager::Clear, 
                                    GetCommon()->mapChunkTimeout));
    
    
    HandleCamera(1, 1);
    
    StormPrintLog(STORM_LOG_INFO, "cMapManager", "Initialized");
}
void cMapManager::HandleCamera(int x, int y) {
    sRect winSize = S_GetWindowSize();
    camera.x = x - (winSize.w / 2);
    camera.y = y - (winSize.h / 2);
    
    if(camera.x <= 0)
        camera.x = 1;
    if(camera.y <= 0)
        camera.y = 1;
    
    CalculateVisible();
}
void cMapManager::Draw() {
    int shiftX = 0;
    int shiftY = 0;
    for(int i = start.x; i <= end.x; i++){
        for(int j = start.y; j <= end.y; j++){
            if(chunks[i][j] != NULL){
                shiftX = camera.x - (i * GetCommon()->mapChunkWidthPx);
                shiftY = camera.y - (j * GetCommon()->mapChunkHeightPx);
                chunks[i][j]->DrawBot(-shiftX, -shiftY);
            } else {
                chunks[i][j] = new cMapChunk();
                char tmpName[50];
                sprintf(tmpName, "%dx%d", i, j);
                switch(chunks[i][j]->Load(tmpName)){
                    case CHUNK_NOT_FOUND:
                        chunks[i][j]->InitEmpty(1);
                        break;
                    case CHUNK_INVALID_FILE:
                        break;
                }
                loadedChunks.push_back(sPoint(i, j));
            }
        }
    }
}
void cMapManager::Clear() {
    if(loadedChunks.size() < 9)
        return;
    for(int i = 0; i < loadedChunks.size(); i++){
        sPoint tmpC = loadedChunks[i];
        cMapChunk *tmpCh = chunks[tmpC.x][tmpC.y];
        
        //Check if this chunk is still needed
        if(tmpC.x >= start.x && tmpC.x <= end.x 
                && tmpC.y >= start.y && tmpC.y <= end.y){
            //This chunk is still needed
            if(tmpCh->GetTimeout() > 0)
                tmpCh->SetTimeout(0);
            continue;
        }
        
        if(tmpCh == NULL){
            loadedChunks.erase(loadedChunks.begin() + i);
            i = (i > 0) ? i - 1 : 0;
            continue;
        }
        
        if(tmpCh->GetTimeout() == 0){
            //If timeout timer is not started, start it
            tmpCh->SetTimeout(S_GetTime());
            continue;
        }
        
        if(S_GetTime() - tmpCh->GetTimeout() >= GetCommon()->mapChunkTimeout){
            //Chunk timeouted. Delete it...
            //TODO: Maybe save chunk file if it was changed ...
            delete tmpCh;
            chunks[tmpC.x][tmpC.y] = NULL;
            loadedChunks.erase(loadedChunks.begin() + i);
            i = (i > 0) ? i - 1 : 0;
            
            StormPrintLog(STORM_LOG_INFO, "cMapManager",
                            "Chunk %dx%d has just been deleted form memory",
                            tmpC.x, tmpC.y);
        }
    }
}
void cMapManager::SaveAll() {
    
}
sMapTile *cMapManager::GetTile(int x, int y) {
    int chunkX = x / GetCommon()->mapChunkWidth;
    int chunkY = y / GetCommon()->mapChunkHeight;
    if(chunks[chunkX][chunkY] == NULL)
            return NULL;
    x -= chunkX * GetCommon()->mapChunkWidth;
    y -= chunkY * GetCommon()->mapChunkHeight;
    return chunks[chunkX][chunkY]->GetTile(x, y);
}
sMapTile *cMapManager::GetTileScreen(int x, int y) {
    x = (x + camera.x) / GetCommon()->mapTileWidth;
    y = (y + camera.y) / GetCommon()->mapTileHeight;
    return GetTile(x, y);
}
cMapChunk *cMapManager::GetChunkScreen(int x, int y) {
    x = (x + camera.x) / GetCommon()->mapChunkWidthPx;
    y = (y + camera.y) / GetCommon()->mapChunkHeightPx;
    return chunks[x][y];
}
void cMapManager::CalculateVisible() {
    start.x = camera.x / GetCommon()->mapChunkWidthPx;
    start.y = camera.y / GetCommon()->mapChunkHeightPx;

    if(start.x < 0)
            start.x = 0;
    if(start.y < 0)
            start.y = 0;

    end.x = start.x + 2;
    end.y = start.y + 2;
}