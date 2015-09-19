/* 
 * File:   cComponent.h
 * Author: master312
 *
 * Created on August 27, 2015, 6:48 AM
 * This is base class for other components
 */

#ifndef CCOMPONENT_H
#define	CCOMPONENT_H
#include "../../../scripts/cLuaEngine.h"
#include "../../../../storm/engine.h"

class cEntity;

class cComponent {
public:
    virtual ~cComponent() { }
    /* Initialize component. Return < 0 if there was an error */
    virtual int Init() { }
    
    virtual void SetEntity(cEntity *e) { entity = e; }
    virtual cEntity *GetEntity() { return entity; }
protected:
    cEntity *entity;
};

#endif	/* CCOMPONENT_H */

