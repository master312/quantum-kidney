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
    
    sRect &GetRect() { return rect; }
    void SetRect(sRect &_rect) { rect = _rect; }
private:
    sRect rect;
};

#endif	/* CCOMCOLLISION_H */

