/* 
 * File:   cMapManager.h
 * Author: master312
 *
 * Created on August 14, 2015, 5:29 PM
 */

#ifndef CMAPMANAGER_H
#define	CMAPMANAGER_H
#include "../../../storm/engine.h"

#include "cMapChunk.h"
#include "cDebgMapEditor.h"
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
    void Clear(void *data);
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
    /* Return trigger value on screen coordinates @x : @y */
    int GetTriggerScreen(int x, int y);
    /* Set trigger at @x, @y to value @v */
    void SetTriggerScreen(int x, int y, int v);
    
    /* If this is set to true, then */
    void SetDrawTriggerGrid(bool b) { drawTriggerGrid = b; }
    bool GetIsDrawTriggerGrid() { return drawTriggerGrid; }
    
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
    /* Weather trigger grid should be drawn */
    bool drawTriggerGrid;
    
    /* Calculate coordinates of visible chunks (start and end) */
    void CalculateVisible();
    
    cDebgMapEditor *debugMapEditor;
};

#endif	/* CMAPMANAGER_H */

