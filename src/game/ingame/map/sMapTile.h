/* 
 * File:   sMapTile.h
 * Author: master312
 *
 * Created on August 13, 2015, 9:38 PM
 */

#ifndef SMAPTILE_H
#define	SMAPTILE_H
#include "../../../storm/engine.h"
#include <vector>

struct sSrcTile {
    /* ID of tileset */
    int tilesetId;
    int loc;
    //TODO: If tile is animated, animation code should be here
    sSrcTile() {
        tilesetId = 0;
        loc = 0;
    }
    sSrcTile(int tsId, int tileLoc) {
        tilesetId = tsId;
        loc = tileLoc;
    }
};

struct sMapTile {
    /* Vector of all layers that are drawn below entities (grass, water...) */
    std::vector<sSrcTile> botLayers;
    /* Vector of all layers that are drawn over entities (tree, fence...)*/
    std::vector<sSrcTile> topLayers;
    
    /* Every tile has 4 triggers, and their size is W=(tileW/2), H=(tileH/2)
     * This array hold ID's of triggers; If value is 0, there is no trigger
     * if value is -1, trigger area is unwalkable
     * [0] - Top left, [1] - Top right, [2] - Bottom left, [3] - Bottom right */
    int triggers[4];
    
    /* This constructor will initialize empty tile */
    sMapTile(){
        triggers[0] = triggers[1] = triggers[2] = triggers[3] = 0;
    }
    
    /* This constructor will create one bottom layer with tile 0 */
    sMapTile(int tilesetId, int a){
        botLayers.push_back(sSrcTile(tilesetId, a));
        triggers[0] = triggers[1] = triggers[2] = triggers[3] = 0;
    }
    
    int CountBot() {
        return (int)botLayers.size();
    }
    
    int CountTop() {
        return (int)topLayers.size();
    }
    
    sSrcTile *GetBot(int layer){
        return &botLayers[layer];
    }
    
    sSrcTile *GetTop(int layer){
        return &topLayers[layer];
    }
};

#endif	/* SMAPTILE_H */

