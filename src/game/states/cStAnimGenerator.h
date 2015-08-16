/* 
 * File:   cStAnimGenerator.h
 * Author: master312
 *
 * Created on August 16, 2015, 6:38 PM
 */

#ifndef CSTANIMGENERATOR_H
#define	CSTANIMGENERATOR_H
#include "../../storm/engine.h"

class cStAnimGenerator : public cStormState {
public:
    cStAnimGenerator();
    ~cStAnimGenerator();
    
    void Init();
    void GraphicsTick();
    void LogicTick();
    void HandleEvents();
    void Pause();
    void Resume();
    void Shutdown();
};

#endif	/* CSTANIMGENERATOR_H */

