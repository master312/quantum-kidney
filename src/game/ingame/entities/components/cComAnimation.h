/* 
 * File:   cComAnimation.h
 * Author: master312
 *
 * Created on September 15, 2015, 9:26 PM
 */

#ifndef CCOMANIMATION_H
#define	CCOMANIMATION_H
#include "cComponent.h"

class cComAnimation : public cComponent {
public:
    cComAnimation(luabridge::LuaRef &table, cEntity *e);
    ~cComAnimation();
    
    bool IsInited() { return animId > 0; }
    uint GetAnimId() { return animId; }
    void SetAnimId(uint _id) { animId = _id; }
private:
    uint animId;
};

#endif	/* CCOMANIMATION_H */

