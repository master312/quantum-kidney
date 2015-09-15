/* 
 * File:   cComPlayerDriver.h
 * Author: master312
 *
 * Created on August 27, 2015, 6:53 AM
 */

#ifndef CCOMPLAYERDRIVER_H
#define	CCOMPLAYERDRIVER_H
#include "cComponent.h"

class cComPlayerDriver : public cComponent {
public:
    cComPlayerDriver(luabridge::LuaRef &table);
    ~cComPlayerDriver();
private:

};

#endif	/* CCOMPLAYERDRIVER_H */

