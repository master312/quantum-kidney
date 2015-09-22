/* 
 * File:   cEntity.cpp
 * Author: master312
 * 
 * Created on August 14, 2015, 7:05 PM
 */

#include "cEntity.h"
#include "cEntityManager.h"

cEntity::cEntity() {
    id = -1;
}
cEntity::cEntity(const std::string &_type){
    id = -1;
    type = _type;
}
cEntity::~cEntity() {
    for(auto &c : components){
        GetCommon()->entityManager->GetSystem(c.first)->UnRegister(c.second);
        delete c.second;
    }
}
void cEntity::AddComponent(std::type_index type, cComponent *component) {
    components[type] = component;
}
