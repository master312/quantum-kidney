/* 
 * File:   cEntity.h
 * Author: master312
 *
 * Created on August 14, 2015, 7:05 PM
 */

#ifndef CENTITY_H
#define	CENTITY_H
#include "../../../storm/engine.h"
#include "../../../storm/cVector2d.h"
#include "../../sCommon.h"
#include "components/cComponent.h"
#include <vector>
#include <typeindex>
#include <map>

class cEntity {
public:
    cEntity();
    cEntity(const std::string &type);
    ~cEntity();
    /* Called just before object deletion */
    void OnDestroy() { }
    
    void SetType(const std::string &_type) { type = _type; }
    std::string& GetType() { return type; }
    void SetId(uint _id) { id = _id; }
    uint GetId() { return id; }
    cVector2d *GetLoc() { return &loc; }
    /* Adds new component to this entity */
    void AddComponent(std::type_index type, cComponent *component);
    /* Returns pointer to component, or nullptr if not found*/
    template <typename T>
    T* GetComponent() {
        auto it = components.find(std::type_index(typeid(T)));
        if (it != components.end()) {
            return dynamic_cast<T*>(it->second);
        }
        return nullptr;
    }
protected:
    uint id;
    cVector2d loc;
    std::string type;
    std::map<std::type_index, cComponent*> components;
};

#endif	/* CENTITY_H */

