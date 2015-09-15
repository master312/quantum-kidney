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
    cComCollision(luabridge::LuaRef &table);
    ~cComCollision();
private:

};

#endif	/* CCOMCOLLISION_H */

