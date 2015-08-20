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
    
    void ShowLoadFile();
    void ShowCreateNew();
    
    void LoadAnim();
    
    void PlayPauseAnim();
    
    void Generate();
    void Save();
private:
    uint spriteTemp;
    uint animationId;
    
    cGuiWidgetInput *frInput;
    cGuiWidgetInput *sInput;
    cGuiWidgetInput *aInput;
    cGuiWidgetInput *fwInput;
    cGuiWidgetInput *fhInput;
    cGuiWidgetButton *gButton;
    cGuiWidgetButton *sButton;

    cGuiWidgetLabel *plCurFrame;
    cGuiWidgetButton *plPlayPause;
    cGuiWidgetInput *plLocX, *plLocY;
    
    cGuiWidgetInput *lAnimFilename;
    cGuiWidgetInput *lAnimSpriteFname;
    
    void InitMainWindow();
    void InitLoadWindow();
    void InitGenWindow();
    void InitPlaybackWindow();
};

#endif	/* CSTANIMGENERATOR_H */

