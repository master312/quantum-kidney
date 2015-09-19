/* 
 * File:   cSysPlayerDriver.h
 * Author: master312
 *
 * Created on September 17, 2015, 6:55 PM
 */

#ifndef CSYSPLAYERDRIVER_H
#define	CSYSPLAYERDRIVER_H
#include "cSystem.h"
#include "../components/cComPlayerDriver.h"
#include "../components/hComDefines.h"
#include "../components/cComPawn.h"

class cSysPlayerDriver : public cSystem {
public:
    cSysPlayerDriver();
    ~cSysPlayerDriver();
    void Tick();
    
    void HandleEvents(void *data);
private:
    
    void HandleEvent(cComPawn *comP);
};

#endif	/* CSYSPLAYERDRIVER_H */

