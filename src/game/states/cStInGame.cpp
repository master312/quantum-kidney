/* 
 * File:   cStInGame.cpp
 * Author: master312
 * 
 * Created on August 13, 2015, 9:03 PM
 */

#include "cStInGame.h"

cStInGame::cStInGame() {
}
cStInGame::~cStInGame() {
}
void cStInGame::Init() {
    S_AddEventHandler(
            new cStormCallbacker(this, &cStInGame::HandleEvents), 
            "cStInGame");
    
    sCommon *tmpC = GetCommon(); 
    
    cMapManager *mapManager = new cMapManager();
    mapManager->Init();
    tmpC->mapManager = mapManager;
    
    cPlayerDriver *playerDriver = new cPlayerDriver();
    playerDriver->Init();
    tmpC->playerDriver = playerDriver;
    
    StormPrintLog(STORM_LOG_INFO, "cStInGame", "State initialized");
}
void cStInGame::GraphicsTick() {
    sCommon *tmpC = GetCommon();
    
    tmpC->mapManager->Draw();
    
    S_RenderText("State: cStInGame", 1, 1);
}
void cStInGame::LogicTick() {
    
}
void cStInGame::HandleEvents() {
    
}
void cStInGame::Pause() {
    S_RemoveEventHandler("cStInGame");
    StormPrintLog(STORM_LOG_INFO, "cStInGame", "State paused");
}
void cStInGame::Resume() {
    S_AddEventHandler(
            new cStormCallbacker(this, &cStInGame::HandleEvents), 
            "cStInGame");
    StormPrintLog(STORM_LOG_INFO, "cStInGame", "State resumed");
}
void cStInGame::Shutdown() {
    S_RemoveEventHandler("cInGame");
    StormPrintLog(STORM_LOG_INFO, "cInGame", "State ended");
}