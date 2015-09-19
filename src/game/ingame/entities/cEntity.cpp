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
}
void cEntity::AddComponent(std::type_index type, cComponent *component) {
    components[type] = component;
}
