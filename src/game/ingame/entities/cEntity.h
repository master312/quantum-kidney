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

class cEntity {
public:
    cEntity();
    ~cEntity();
    /* Called just before object deletion */
    void OnDestroy() { }
    
    void SetId(int _id) { id = _id; }
    int GetId() { return id; }
    cVector2d *GetLoc() { return &loc; }
    /* Adds new component to this entity */
    void AddComponent(cComponent *component);
    /* Returns pointer to component, or nullptr if not found*/
    template <typename T> T GetComponent();
protected:
    int id;
    cVector2d loc;
    
    std::vector<cComponent*> components;
};

#endif	/* CENTITY_H */

