/* 
 * File:   cStAnimGenerator.h
 * Author: master312
 *
 * Created on August 16, 2015, 6:38 PM
 */

#ifndef CSTANIMGENERATOR_H
#define	CSTANIMGENERATOR_H
#include "../../storm/engine.h"
#include "../../storm/gui/cGuiManager.h"
#include <vector>

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
    void LoadAnim();
    
    
private:
    uint animationId;
    
    cGuiWidgetInput *frInput;
    cGuiWidgetInput *sInput;
    cGuiWidgetInput *aInput;
    cGuiWidgetInput *fwInput;
    cGuiWidgetInput *fhInput;
    cGuiWidgetButton *aButton;
    cGuiWidgetContainer *cont;    
};

#endif	/* CSTANIMGENERATOR_H */

