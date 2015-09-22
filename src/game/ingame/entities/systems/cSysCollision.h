/* 
 * File:   cSysCollision.h
 * Author: master312
 *
 * Created on September 21, 2015, 8:20 PM
 * TODO: Optimize, by creating entity groups
 */

#ifndef CSYSCOLLISION_H
#define	CSYSCOLLISION_H
#include "cSystem.h"
#include "../components/cComCollision.h"

class cSysCollision : public cSystem {
public:
    cSysCollision();
    ~cSysCollision();
    
    void Tick();
    void Draw();
    
    /* Handled storm console commands */
    void HandleCmd(void *data);
private:
    bool debugDraw;
};

#endif	/* CSYSCOLLISION_H */

