/* 
 * File:   cSysAnimation.h
 * Author: master312
 *
 * Created on September 16, 2015, 8:12 PM
 */

#ifndef CSYSANIMATION_H
#define	CSYSANIMATION_H
#include <vector>
#include "../components/cComAnimation.h"
#include "cSystem.h"

class cSysAnimation : public cSystem {
public:
    cSysAnimation();
    ~cSysAnimation();
    
    void Tick();
    void Draw();
private:
    
};

#endif	/* CSYSANIMATION_H */

