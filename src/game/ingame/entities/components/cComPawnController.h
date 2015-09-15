/* 
 * File:   cComPawnController.h
 * Author: master312
 *
 * Created on August 27, 2015, 6:51 AM
 */

#ifndef CCOMPAWNCONTROLLER_H
#define	CCOMPAWNCONTROLLER_H
#include "cComponent.h"

class cComPawnController : public cComponent {
public:
    cComPawnController(luabridge::LuaRef &table);
    ~cComPawnController();
private:

};

#endif	/* CCOMPAWNCONTROLLER_H */

