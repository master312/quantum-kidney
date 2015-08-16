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
    animationId = 0;
}
cStAnimGenerator::~cStAnimGenerator() {
}
void cStAnimGenerator::Init() {
    cont = new cGuiWidgetContainer("CONT_ANIM",
                                   "Anim editor",
                                    20, 20, 300, 300,
                                    false, false, false, false);
    S_GuiAddWidget(cont);
    
    sInput = new cGuiWidgetInput("INPUT_SPRITE_ID", 0, 0, 300, 30, 
                                 "sprite filename");                     
    aInput = new cGuiWidgetInput("INPUT_ANIMATION_ID", 0, 40, 300, 30,
                                  "Animation filename");                 
    fwInput = new cGuiWidgetInput("INPUT_FRAME_WIDTH", 0, 80, 80, 30);            
    fhInput = new cGuiWidgetInput("INPUT_FRAME_HEIGHT", 0, 120, 80, 30);
    frInput = new cGuiWidgetInput("INPUT_FRAMERATE", 0, 160, 80, 30);
    aButton = new cGuiWidgetButton("BUTTON_CREATE_ANIM", "GO", 50, 250, true,
                                    cStormCallbacker(this, 
                                        &cStAnimGenerator::LoadAnim));
    
    
    cont->AddChild(sInput);
    cont->AddChild(fwInput);
    cont->AddChild(fhInput);
    cont->AddChild(aButton);
    cont->AddChild(aInput);
    cont->AddChild(frInput);
    
}
void cStAnimGenerator::GraphicsTick() {
    S_RenderText("State: cStAnimGenerator", 1, 1);
    if(animationId > 0){
    S_DrawAnimation(animationId, 400, 400);
    }
    
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
    std::cout<<"test"<<std::endl;
    
    uint spriteTemp = S_LoadTexture(sInput->GetText());
    if(spriteTemp == 0){
        return;
    }
    std::vector<uint> frames;

    sTexture *texture = S_GetTexture(spriteTemp);
    
    int horizontal = texture->width/atoi(fwInput->GetText().c_str());
    int vertical = texture->height/atoi(fhInput->GetText().c_str());
    int w = atoi(fwInput->GetText().c_str());
    int h = atoi(fhInput->GetText().c_str());
    int framerate = atoi(frInput->GetText().c_str());
    
    
    for(int j = 0; j < horizontal; j++){
        for(int k = 0; k < vertical; k++){
            uint section = S_CreateSection(spriteTemp, k*w, j*h, w, h);
            frames.push_back(section);
        }
    }
    
    animationId = S_CreateAnimation(frames, framerate, false);
    S_SaveAnimation(animationId, aInput->GetText());
    
}
