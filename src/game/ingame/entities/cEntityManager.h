/* 
 * File:   cEntityManager.h
 * Author: master312
 *
 * Created on September 16, 2015, 8:24 PM
 */

#ifndef CENTITYMANAGER_H
#define	CENTITYMANAGER_H
#include <vector>
#include <iostream>
#include <map>
#include "cEntity.h"
#include "cEntityFactory.h"
#include "systems/cSystem.h"
#include "../../../storm/engine.h"

class cEntityManager {
public:
    cEntityManager();
    ~cEntityManager();
    
    /* Creates entity of @type and return pointer to it */
    cEntity *CreateEntity(const std::string& type);
    
    void Draw();
    void Tick();
    
    template <typename T>
    cSystem *GetSystem() {
        auto it = systems.find(std::type_index(typeid(T)));
        if (it != systems.end()) {
            return dynamic_cast<T*>(it->second);
        }
        return nullptr;
    }
    cSystem *GetSystem(std::type_index type) {
        return systems[type];
    }
private:
    cEntityFactory *entityFactory;
    /* Map of all entities */
    std::map<uint, cEntity*> entities;
    uint nextId;
    
    std::map<std::type_index, cSystem*> systems;
    /* Vector of systems that need to go through graphics(Draw) tick */
    std::vector<cSystem*> graphSystems;
};

#endif	/* CENTITYMANAGER_H */

