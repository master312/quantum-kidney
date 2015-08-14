/* 
 * File:   cMapChunk.h
 * Author: master312
 *
 * Created on August 13, 2015, 9:36 PM
 */

#ifndef CMAPCHUNK_H
#define	CMAPCHUNK_H
#define CHUNK_NOT_FOUND -1
#define CHUNK_INVALID_FILE -2
#include <iostream>
#include <vector>
#include <map>
#include "sMapTile.h"
#include "../../storm/engine.h"
#include "../sCommon.h"
/* TODO:
 *  Optimize MABY...: Create new vector that will store coordinates of tiles that 
 * have top layer. So when calling DrawTop(...) we do not need to go trough
 * all tiles, instend go just trough 'top tiles' vector 
 * 
 *  Optimize: Do not go trough all tiles on every draw. Instend draw tiles 
 * between 'tileStart' and 'tileEnd' based on map shifting location 
 * and screen size */

struct sMapTileset{
    /* Pointer to tileset's texture*/
    sTexture *texture;
    /* ID of texture in storm texture manager */
    uint id;
    /* Size of tileset in tiles */
    int width, height;
    
    sMapTileset() { texture = NULL; id = 0; width = height = 0; }
    sMapTileset(sTexture *txt, uint _id){
        texture = txt;
        id = _id;
        width = texture->width / GetCommon()->mapTileWidth;
        height = texture->height / GetCommon()->mapTileHeight;
    }
};

class cMapChunk {
public:
    cMapChunk();
    ~cMapChunk();
    
    /* Initialize empty chunk, filled with tile 0 */
    void InitEmpty(int tilesetId);
    /* Load map from file. @_filename should be only name of file
     * without extension or location. 
     * Return CHUNK_NOT_FOUND or CHUNK_INVALID_FILE */
    int Load(std::string _filename);
    /* Save map to file. @_filename should be only name of file
     * without extension or location. Return false on error */
    bool Save(std::string _filename);
    
    /* Draw bottom layer on screen, on screen coordinates @x, @y */
    void DrawBot(int x, int y);
    /* Draw top layer on screen, on screen coordinates @x, @y */
    void DrawTop(int x, int y);
    /* Draws bottom layer of single tile */
    void DrawTileBot(int tileX, int tileY, int destX, int destY);
    /* Draws top layer of single tile */
    void DrawTileTop(int tileX, int tileY, int destX, int destY);
    
    void SetName(std::string _name) { name = _name; }
    std::string GetName() { return name; }
    sMapTile *GetTile(int x, int y) { return &tiles[x][y]; }
    void SetTimeout(Uint32 _time) { timeout = _time; }
    Uint32 GetTimeout() { return timeout; }
private:
    std::string filename;
    std::string name;
    
    std::vector< std::vector<sMapTile> > tiles;
    /* Map of tileset ID's and loaded texture ID's used by this chunk 
     * <tilesetId, tilesetObject> */
    std::map<int, sMapTileset> tilesets;
    
    /* Temporary rectangle used by drawing methods */
    sRect tmpRect;
    
    /* Used by map manager class to delete chunk from memory on timeout */
    Uint32 timeout;
    
    /* Load all tileset's needed for this map. Tileset id's should 
     * already be pushed in 'tilesets' map.
     * If tilesets are already loaded, it will be ignored */
    void LoadTilesets();
    /* Draws @tile (sSrcTile) at @x:@y on screen*/
    void DrawTile(sSrcTile *tile, int x, int y);
};

#endif	/* CMAPCHUNK_H */

