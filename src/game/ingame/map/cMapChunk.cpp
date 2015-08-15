/* 
 * File:   cMapChunk.cpp
 * Author: master312
 * 
 * Created on August 13, 2015, 9:36 PM
 */

#include "cMapChunk.h"

cMapChunk::cMapChunk() {
    timeout = 0;
    tmpRect.w = GetCommon()->mapTileWidth;
    tmpRect.h = GetCommon()->mapTileHeight;
}
cMapChunk::~cMapChunk() {
}
void cMapChunk::InitEmpty(int tilesetId) {
    tilesets[tilesetId] = sMapTileset();    //Push tileset into 'tilesets' std::map
    
    for(int i = 0; i < GetCommon()->mapChunkWidth; i++){
        std::vector<sMapTile> tmp;
        for(int j = 0; j < GetCommon()->mapChunkHeight; j++){
            tmp.push_back(sMapTile(tilesetId, 1));
        }
        tiles.push_back(tmp);
        tmp.clear();
    }
    
    LoadTilesets(); //Load tileset used by this map
    
    StormPrintLog(STORM_LOG_INFO, "cMapChunk", 
                "Empty chunk initialized with tileset %d", tilesetId);
}
int cMapChunk::Load(std::string _filename) {
    return CHUNK_NOT_FOUND;
}
bool cMapChunk::Save(std::string _filename) {
    
}
void cMapChunk::DrawBot(int x, int y) {
    int destX, destY;
    for(int i = 0; i < GetCommon()->mapChunkWidth; i++){
        destX = x + (i * GetCommon()->mapTileWidth);
        for(int j = 0; j < GetCommon()->mapChunkHeight; j++){
            destY = y + (j * GetCommon()->mapTileHeight);
            DrawTileBot(i, j, destX, destY);
        }
    }
}
void cMapChunk::DrawTop(int x, int y) {
    int destX, destY;
    for(int i = 0; i < GetCommon()->mapChunkWidth; i++){
        destX = x + (i * GetCommon()->mapTileWidth);
        for(int j = 0; j < GetCommon()->mapChunkHeight; j++){
            destY = y + (j * GetCommon()->mapTileHeight);
            DrawTileTop(i, j, destX, destY);
        }
    }
}
void cMapChunk::DrawTileBot(int tileX, int tileY, int destX, int destY) {
    sMapTile *tmpTile = &tiles[tileX][tileY];
    
    for(int i = 0; i < tmpTile->CountBot(); i++)
        DrawTile(&tmpTile->botLayers[i], destX, destY);
}
void cMapChunk::DrawTileTop(int tileX, int tileY, int destX, int destY) {
    sMapTile *tmpTile = &tiles[tileX][tileY];
    
    for(int i = 0; i < tmpTile->CountTop(); i++)
        DrawTile(&tmpTile->topLayers[i], destX, destY);
}
//Private functions
void cMapChunk::LoadTilesets() {
    for (auto const& ts : tilesets){
        if(ts.second.texture != NULL)
            continue; //If texture is loaded skip...
        
        char tmpName[50];
        sprintf(tmpName, "tilesets/%d.png", ts.first);
        uint tmpId = S_LoadTexture(tmpName);
        
        if(tmpId == 0)
            continue;
    
        tilesets[ts.first] = sMapTileset(S_GetTexture(tmpId), tmpId);
    }
}
void cMapChunk::DrawTile(sSrcTile *tile, int x, int y) {
    sMapTileset *ts = &tilesets[tile->tilesetId];
    
    if(ts->texture == NULL)  //Tileset for this tile is not loaded!
        return;              //TODO: Handle this somehow...

    //Convert tile->loc to coordinates on tileset texture
    if(tile->loc < ts->width){
        tmpRect.x = tile->loc;
        tmpRect.y = 0;
    } else {
        tmpRect.y = tile->loc / ts->width;
        tmpRect.x = tile->loc - (tmpRect.y * ts->width);
    }
    /* * * * * * * * * * */
    
    //Convert tile coordinates to pixel coordinates
    tmpRect.x *= GetCommon()->mapTileWidth;
    tmpRect.y *= GetCommon()->mapTileHeight;
    
    S_DrawTextureCropped(ts->id, &tmpRect, x, y);
}