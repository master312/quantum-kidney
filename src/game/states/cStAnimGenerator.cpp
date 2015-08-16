/* 
 * File:   cStAnimGenerator.cpp
 * Author: master312
 * 
 * Created on August 16, 2015, 6:38 PM
 * 
 * 
 * animation file name input DONE
 * sprite file name input DONE
 * frame size wh input DONE
 * 
 * 
 * 
 */

#include "cStAnimGenerator.h"

cStAnimGenerator::cStAnimGenerator() {
}
cStAnimGenerator::~cStAnimGenerator() {
}
void cStAnimGenerator::Init() {
    cont = new cGuiWidgetContainer("CONT_ANIM",
                                   "Anim editor",
                                    20, 20, 300, 300);
    S_GuiAddWidget(cont);
    
    sInput = new cGuiWidgetInput("INP_SP", 0, 0, 300, 30);
    aInput = new cGuiWidgetInput("INP_ANIM", 0, 40, 300, 30);
    fwInput = new cGuiWidgetInput("INP_FRAME_WIDTH", 0, 80, 150, 30);
    fhInput = new cGuiWidgetInput("INP_FRAME_HEIGHT", 0, 120, 150, 30);
    aButton = new cGuiWidgetButton("BUTTON_CREATE_ANIM", "GO", 50, 250, true,
                                    cStormCallbacker(this, 
                                        &cStAnimGenerator::LoadAnim));
    
    cont->AddChild(sInput);
    cont->AddChild(fwInput);
    cont->AddChild(fhInput);
    cont->AddChild(aButton);
    cont->AddChild(aInput);
    
}
void cStAnimGenerator::GraphicsTick() {
    S_RenderText("State: cStAnimGenerator", 1, 1);
    
    if(S_IsTextInput())
        S_RenderText("INPUT!!!!(Text)", 400, 400);
    else S_RenderText("NOT", 400, 400);
}
void cStAnimGenerator::LogicTick() {
}
void cStAnimGenerator::HandleEvents() {
}
void cStAnimGenerator::Pause() {
}
void cStAnimGenerator::Resume() {
}
void cStAnimGenerator::Shutdown() {
}
void cStAnimGenerator::LoadAnim() {
    std::cout << aInput->GetText() << std::endl;
    std::cout << "KLIKN'O SI DUGME SINE" << std::endl;
}
