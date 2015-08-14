/* 
 * File:   cMapManager.h
 * Author: master312
 *
 * Created on August 14, 2015, 5:29 PM
 */

#ifndef CMAPMANAGER_H
#define	CMAPMANAGER_H
#include "../../storm/engine.h"
#include "../sCommon.h"
#include "cMapChunk.h"
#include <vector>
/* TODO:
 *  Out of range check in CalculateVisible() */

class cMapManager {
public:
    cMapManager();
    ~cMapManager();
    
    /* Initialize map manager */
    void Init();
    
    /* Handle camera movement 
     * @x and @y is position used to calculate camera (player position) */
    void HandleCamera(int x, int y);
    
    /* Draws map to screen*/
    void Draw();
    
    /* Delete unused chunks. This method should not be called manually
     * Method is called on interval */
    void Clear();
    
    /* Save all changes made to map chunks */
    void SaveAll();
    
    /* Returns pointer to tile
     * @x and @y are global map coordinates, in tiles */
    sMapTile *GetTile(int x, int y);
    /* Returns pointer to tile
     * @x and @y are coordinates on screen */
    sMapTile *GetTileScreen(int x, int y);
    /* Returns pointer to map chunk. @x and @y are coordinates on screen */
    cMapChunk *GetChunkScreen(int x, int y);
    
    sPoint *GetCamera() { return &camera; }
private:
    std::vector< std::vector<cMapChunk*> > chunks;
    std::vector<sPoint> loadedChunks;
    
    /* Coordinates of possible visible chunks on world map 
     * Chunks on coordinates between start and end (including start and end) are visible*/
    sPoint start;
    sPoint end;
    /* Camera coordinates */
    sPoint camera;

    /* Calculate coordinates of visible chunks (start and end) */
    void CalculateVisible();
};

#endif	/* CMAPMANAGER_H */

