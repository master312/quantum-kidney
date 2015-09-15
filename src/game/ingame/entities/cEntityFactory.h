/* 
 * File:   cEntityFactory.h
 * Author: master312
 *
 * Created on September 15, 2015, 6:18 PM
 */

#ifndef CENTITYFACTORY_H
#define	CENTITYFACTORY_H
#define DIR_ENTITY_SCRIPTS "data/lua/entities/"
#define DIR_FRAMEWORK_SCRIPTS "data/lua/framework/"
#include "cEntity.h"
#include "../../scripts/cLuaEngine.h"
#include "../../../storm/engine.h"
#include <iostream>
#include <vector>

using namespace luabridge;

class cEntityFactory {
public:
    cEntityFactory();
    ~cEntityFactory();
    
    /* Initialize entity factory and lua engine 
     * Also registers global C++ functions to lua engine */
    void Init();
    /* Load all entity and framework scripts 
     * From folders DIR_ENTITY_SCRIPTS, and DIR_FRAMEWORK_SCRIPTS */
    void LoadScripts();
    
    /* Create entity of @type and return reference to it 
     * This method will return nullptr if entity type 
     * or parameters in script are invalid */
    cEntity *CreateEntity(const std::string& type);
private:
    cLuaEngine *luaEngine;
    
    template <typename T>
    void AddComponent(cEntity* e, LuaRef& comTable) {
        if(!comTable.isNil()){
            e->AddComponent(std::type_index(typeid(T)), new T(comTable));
        }
    }
};

#endif	/* CENTITYFACTORY_H */

