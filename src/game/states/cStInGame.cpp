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
    
    cCameraManager *cameraManager = new cCameraManager();
    tmpC->cameraManager = cameraManager;
    
    cEntityManager *entityManager = new cEntityManager();
    tmpC->entityManager = entityManager;
    
    entityManager->CreateEntity("player");
    entityManager->CreateEntity("creep");
    
    InitNewGame();
    
    StormPrintLog(STORM_LOG_INFO, "cStInGame", "State initialized");
}
void cStInGame::InitNewGame() { //Private method...
    
}
void cStInGame::GraphicsTick() {
    sCommon *tmpC = GetCommon();
    
    //tmpC->mapManager->Draw();
    tmpC->entityManager->Draw();
    
    S_RenderText("State: cStInGame", 1, 1);
}
void cStInGame::LogicTick() {
    sCommon *tmpC = GetCommon();
    
    tmpC->cameraManager->Tick();
    tmpC->entityManager->Tick();
    
}
void cStInGame::HandleEvents(void *data) {

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