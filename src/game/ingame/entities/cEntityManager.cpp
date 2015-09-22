#include "cEntityManager.h"
#include "systems/cSysAnimation.h"
#include "systems/cSysPlayerDriver.h"
#include "systems/cSysCollision.h"
#include "systems/cSysImage.h"

cEntityManager::cEntityManager() {
    graphSystems.push_back(new cSysAnimation());
    systems[std::type_index(typeid(cSysAnimation))] = graphSystems.back();
    systems[std::type_index(typeid(cSysPlayerDriver))] = new cSysPlayerDriver();
    graphSystems.push_back(new cSysImage());
    systems[std::type_index(typeid(cSysImage))] = graphSystems.back();
    graphSystems.push_back(new cSysCollision());
    systems[std::type_index(typeid(cSysCollision))] = graphSystems.back();
    
    entityFactory = new cEntityFactory();
    entityFactory->Init();
    entityFactory->LoadScripts();
    nextId = 1;
}
cEntityManager::~cEntityManager() {
    for(auto &s : systems){
        delete s.second;
    }
    for(auto &e : entities){
        delete e.second;
    }
    if(entityFactory != NULL){
        delete entityFactory;
    }
    
    systems.clear();
    entities.clear();
}
cEntity *cEntityManager::CreateEntity(const std::string& type) {
    cEntity *tmpE = entityFactory->CreateEntity(type);
    if(tmpE == nullptr){
        StormPrintLog(STORM_LOG_ERROR, "cEntetyManager",
                      "Could not create entity of type '%s'", type.c_str());
        return nullptr;
    }
    
    tmpE->SetId(nextId);
    entities[nextId] = tmpE;
    nextId += 1;
    
    return tmpE;
}
void cEntityManager::Draw() {
    for(auto &s : graphSystems){
        s->Draw();
    }
}
void cEntityManager::Tick() {
    for(auto &s : systems){
        s.second->Tick();
    }
}