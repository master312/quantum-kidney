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
    cComAnimation(luabridge::LuaRef &table);
    ~cComAnimation();
private:

};

#endif	/* CCOMANIMATION_H */

