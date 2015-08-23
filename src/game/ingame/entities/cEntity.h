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

enum eEntityType {undefined, character, npc, object};

class cEntity {
public:
    cEntity();
    virtual ~cEntity();
    /* Called just before object deletion */
    virtual void OnDestroy() { }
    
    void SetId(int _id) { id = _id; }
    int GetId() { return id; }
    cVector2d *GetLoc() { return &loc; }
    
    eEntityType GetType() { return type; }
    
    bool IsDefined() { return type != undefined; }
    bool IsPawn() { return type == character || type == npc; }
    bool IsCharacter() { return type == character; }
    bool IsNpc() { return type == npc; }
    bool IsObject() { return type == object; }
protected:
    int id;
    cVector2d loc;
    
    eEntityType type;
};

#endif	/* CENTITY_H */

