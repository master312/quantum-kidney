/* 
 * File:   cCameraManager.h
 * Author: master312
 *
 * Created on August 23, 2015, 4:11 PM
 */

#ifndef CCAMERAMANAGER_H
#define	CCAMERAMANAGER_H
#include "../sCommon.h"
#include "map/cMapManager.h"
#include "../../storm/cVector2d.h"
#include "cPlayerDriver.h"

class cCameraManager {
public:
    cCameraManager();
    ~cCameraManager();
    
    void Tick();
private:

};

#endif	/* CCAMERAMANAGER_H */

