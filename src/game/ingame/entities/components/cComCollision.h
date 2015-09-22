/* 
 * File:   cComCollision.h
 * Author: master312
 *
 * Created on August 27, 2015, 6:51 AM
 */

#ifndef CCOMCOLLISION_H
#define	CCOMCOLLISION_H
#include "cComponent.h"

class cComCollision : public cComponent {
public:
    cComCollision(luabridge::LuaRef &table, cEntity *e);
    ~cComCollision();
    
    bool IsInited() { return !rect.IsZero(); }
    
    void HandleCollision(cComCollision *col);
    
    sRect &GetRect() { return rect; }
    void SetRect(sRect &_rect) { rect = _rect; }
    /* Returns collider rect with entity coordinates include */
    sRect &GetCollider();
private:
    /* Collision rectangle */
    sRect rect;
    /* Collision rectangle with entity coordinates included */
    sRect collider;
    
    /* This is pointer to LUA function will be called when this collider 
     * collide with other collider */
    //luabridge::LuaRef luaCallback;
};

#endif	/* CCOMCOLLISION_H */

