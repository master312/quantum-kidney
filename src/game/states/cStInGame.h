/* 
 * File:   cStInGame.h
 * Author: master312
 *
 * Created on August 13, 2015, 9:03 PM
 */

#ifndef CSTINGAME_H
#define	CSTINGAME_H
#include "../../storm/engine.h"
#include "../sCommon.h"
#include "../ingame/map/cMapManager.h"
#include "../ingame/cPlayerDriver.h"
#include "../ingame/cEntityManager.h"
#include "../ingame/cCameraManager.h"

class cStInGame : public cStormState {
public:
    cStInGame();
    ~cStInGame();
    
    void Init();
    void GraphicsTick();
    void LogicTick();
    void HandleEvents();
    void Pause();
    void Resume();
    void Shutdown();
private:
    //This is temp method used to initialize test game scenario
    void InitNewGame();
};

#endif	/* CSTINGAME_H */

