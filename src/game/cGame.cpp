/* 
 * File:   cGame.cpp
 * Author: master312
 * 
 * Created on August 13, 2015, 8:28 PM
 */

#include "cGame.h"

cGame::cGame() {
}

cGame::~cGame() {
    S_Quit();
}

void cGame::Start() {
    srand(time(0));
    
    if(!S_InitEngine(STORM_API_SDL2)){
        return;
    }
    
    S_ResizeWindow(864, 486);
    S_AddMainState(new cStMainMenu());  //Creates main sate
    SDL_Delay(10);
    
    while(S_IsRunning()){
        S_ClearScreen();
        S_Tick();
        SDL_Delay(1);
    }
}

