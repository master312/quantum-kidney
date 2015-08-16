/* 
 * File:   cStMainMenu.h
 * Author: master312
 *
 * Created on August 13, 2015, 8:38 PM
 */

#ifndef CSTMAINMENU_H
#define	CSTMAINMENU_H
#include "../../storm/engine.h"
#include "cStInGame.h"
#include "cStAnimGenerator.h"

class cStMainMenu : public cStormState {
public:
    cStMainMenu();
    ~cStMainMenu();

    void Init();
    void GraphicsTick();
    void LogicTick();
    void HandleEvents();
    void Pause();
    void Resume();
    void Shutdown();
};

#endif	/* CSTMAINMENU_H */

