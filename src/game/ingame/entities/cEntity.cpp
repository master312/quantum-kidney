/* 
 * File:   cEntity.cpp
 * Author: master312
 * 
 * Created on August 14, 2015, 7:05 PM
 */

#include "cEntity.h"

cEntity::cEntity() {
    id = -1;
}
cEntity::~cEntity() {
}
void cEntity::AddComponent(cComponent *component) {
    components.push_back(component);
}
template <typename T> T cEntity::GetComponent() {
    for(auto &i : components){
        T *toReturn = dynamic_cast<T*> (i);
        if(toReturn != nullptr){
            return toReturn;
        }
    }
    return nullptr;
}