/* 
 * File:   cStAnimGenerator.cpp
 * Author: master312
 * 
 * Created on August 16, 2015, 6:38 PM
 * 
 */

#include "cStAnimGenerator.h"
#include "cStMainMenu.h"

cStAnimGenerator::cStAnimGenerator() {
    spriteTemp = 0;
    animationId = 0;
    aInput = NULL;
}
cStAnimGenerator::~cStAnimGenerator() {
}
void cStAnimGenerator::Init() {
    InitMainWindow();
    InitPlaybackWindow();
}
void cStAnimGenerator::GraphicsTick() {
    S_RenderText("State: cStAnimGenerator", 1, 1);
    if(animationId > 0){
        if(plLocX->GetText().size() > 0 && plLocY->GetText().size() > 0){
            S_DrawAnimation(animationId, 
                            atoi(plLocX->GetText().c_str()), 
                            atoi(plLocY->GetText().c_str()));
        }else{
            S_DrawAnimation(animationId, 400, 400);
        }
        cAnimation *anim = S_GetAnimation(animationId);
        plCurFrame->SetTextArgs("Frame: %d / %d", 
                            anim->GetCurFrame(), 
                            anim->GetFramesCount() - 1);
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
void cStAnimGenerator::ShowLoadFile(void *data){
    S_GuiHideWidgetByName("CONT_ANIM_MAIN");
    InitLoadWindow();
    S_GuiShowWidgetByName("CONT_ANIM_LOAD");
}
void cStAnimGenerator::ShowCreateNew(void *data){
    S_GuiHideWidgetByName("CONT_ANIM_MAIN");
    InitGenWindow();
    S_GuiShowWidgetByName("CONT_ANIM_GEN");
}
void cStAnimGenerator::LoadAnim(void *data){
    if(animationId != 0){
        S_RemoveAnimation(animationId);
    }
    animationId = S_LoadAnimation(lAnimFilename->GetText());
    if(animationId == 0)
        return;
    
    lAnimSpriteFname->SetText(S_GetTexture(
                        S_GetSection(
                            S_GetAnimation(animationId)->GetFrame(0))->texture)
                    ->filename);
    
    S_GuiShowWidgetByName("CONT_ANIM_PLAY"); 
    InitGroupsWindow();
    std::map<std::string, sAnimFrameGroup> *tmpG;
    tmpG = S_GetAnimation(animationId)->GetFrameGroups();
    int count = tmpG->size();
    
    if(count == 0)
        return;
    
    for(auto &kk : *tmpG){
        char tmpCh[50];
        sprintf(tmpCh, "%s %d-%d", kk.first.c_str(), 
                                    kk.second.start,
                                    kk.second.end);
        gAnimList->AddItem(tmpCh);
    }
}
void cStAnimGenerator::PlayPauseAnim(void *data) {
    if(animationId == 0)
        return;
    if(S_GetAnimation(animationId)->IsPaused()){
        S_ResumeAnimation(animationId);
    }else{
        S_PauseAnimation(animationId);
    }
}
void cStAnimGenerator::CreateGroup(void *data) {
    int start = atoi(gAnimStart->GetText().c_str());
    int end = atoi(gAnimEnd->GetText().c_str());
    S_GetAnimation(animationId)->AddFrameGroup(gAnimName->GetText(),
                                                start, end);
    
    char tmp[50];
    sprintf(tmp, "%s %d-%d", gAnimName->GetText().c_str(), start, end);
    gAnimList->AddItem(tmp);
}
void cStAnimGenerator::Generate(void *data) {
    if(animationId > 0){
        if(!S_GetAnimation(animationId)->IsLoadedFromFile() && spriteTemp > 0){
            S_UnloadTexture(spriteTemp);
        }
        S_RemoveAnimation(animationId);
        spriteTemp = 0;
        animationId = 0;
    }
    spriteTemp = S_LoadTexture(sInput->GetText());
    if(spriteTemp == 0){
        return;
    }
    std::vector<uint> frames;

    sTexture *texture = S_GetTexture(spriteTemp);
    
    int w = atoi(fwInput->GetText().c_str());
    int h = atoi(fhInput->GetText().c_str());
    int horizontal = texture->width / w;
    int vertical = texture->height / h;
    int framerate = atoi(frInput->GetText().c_str());
    
    for(int j = 0; j < horizontal; j++){
        for(int k = 0; k < vertical; k++){
            uint section = S_CreateSection(spriteTemp, k * w, j * h, w, h);
            frames.push_back(section);
        }
    }
    
    animationId = S_CreateAnimation(frames, framerate, false);
    S_GuiShowWidgetByName("CONT_ANIM_PLAY");
    InitGroupsWindow();
}
void cStAnimGenerator::Save(void *data) {
    if(animationId == 0)
        return;
    
    if(aInput != NULL)
        S_SaveAnimation(animationId, aInput->GetText());
    else
        S_SaveAnimation(animationId, lAnimFilename->GetText());
}
//Private methods
void cStAnimGenerator::InitMainWindow() {
    cGuiWidgetContainer *cont = new cGuiWidgetContainer("CONT_ANIM_MAIN",
                                                "Anim editor",
                                                 5, 20, 250, 100,
                                                 false, false, false, false);
    S_GuiAddWidget(cont);
    
    cGuiWidgetButton *gButton = new cGuiWidgetButton("BUTTON_SHOW_GEN_WINDOW", 
                                    "Create new animation", 
                                    5, 5, true,
                                    cStormCallbacker(this, 
                                            &cStAnimGenerator::ShowCreateNew)
                                    );
    cont->AddChild(gButton);
    gButton = new cGuiWidgetButton("BUTTON_SHOW_EDIT_WINDOW", 
                                    "Edit existing animation", 
                                    4, 40, true,
                                    cStormCallbacker(this, 
                                            &cStAnimGenerator::ShowLoadFile)
                                    );
    cont->AddChild(gButton);
}
void cStAnimGenerator::InitLoadWindow(){
    cGuiWidgetContainer *cont = new cGuiWidgetContainer("CONT_ANIM_LOAD",
                                                "Anim loader",
                                                 5, 20, 300, 240,
                                                 false, false, false, false);
    cont->isOnScreen = false;
    S_GuiAddWidget(cont);
    
    lAnimFilename = new cGuiWidgetInput("INPUT_LOAD_FNAME", 0, 2, 300, 30,
                                        "Animation Filename");
    lAnimSpriteFname = new cGuiWidgetInput("INPUT_LOAD_SPNAME", 0, 40, 300, 30,
                                        "Sprite filename", false);
    cGuiWidgetButton *lBtn = new cGuiWidgetButton("BUTTON_LOAD_ANIM", 
                                    "Load animation", 
                                    10, 200, true,
                                    cStormCallbacker(this, 
                                                    &cStAnimGenerator::LoadAnim)
                                    );
    cGuiWidgetButton *sBtn = new cGuiWidgetButton("BUTTON_LOAD_SAVE", 
                                    "Save", 
                                    135, 200, true,
                                    cStormCallbacker(this, 
                                                    &cStAnimGenerator::Save)
                                    );
    
    
    cont->AddChildren(4, lAnimFilename, lAnimSpriteFname, lBtn, sBtn);
}
void cStAnimGenerator::InitGenWindow() {
    cGuiWidgetContainer *cont = new cGuiWidgetContainer("CONT_ANIM_GEN",
                                                "Anim editor",
                                                 5, 20, 300, 240,
                                                 false, false, false, false);
    cont->isOnScreen = false;
    S_GuiAddWidget(cont);
    
    sInput = new cGuiWidgetInput("INPUT_SPRITE_FNAME", 0, 0, 300, 30, 
                                    "sprite filename");                     
    aInput = new cGuiWidgetInput("INPUT_ANIMATION_FNAME", 0, 40, 300, 30,
                                    "Animation filename");                 
    fwInput = new cGuiWidgetInput("INPUT_FRAME_WIDTH", 0, 80, 80, 30,
                                    "FRW");            
    fhInput = new cGuiWidgetInput("INPUT_FRAME_HEIGHT", 0, 120, 80, 30,
                                    "FRH");
    frInput = new cGuiWidgetInput("INPUT_FRAMERATE", 0, 160, 80, 30,
                                    "N_FPS");
    gButton = new cGuiWidgetButton("BUTTON_GENERATE_ANIM", 
                                    "Generate", 
                                    25, 200, true,
                                    cStormCallbacker(this, 
                                                    &cStAnimGenerator::Generate)
                                    );
    sButton = new cGuiWidgetButton("BUTTON_SAVE_ANIM", 
                                    "Save to file", 
                                    125, 200, true,
                                    cStormCallbacker(this, 
                                                    &cStAnimGenerator::Save)
                                    );
    
    cont->AddChildren(7, sInput, aInput, fwInput, fhInput, 
                        frInput, gButton, sButton);
}
void cStAnimGenerator::InitPlaybackWindow() {
    cGuiWidgetContainer *cont = new cGuiWidgetContainer("CONT_ANIM_PLAY",
                                                "Playback",
                                                5, 270, 300, 150,
                                                true, false, false, false);
    cont->isOnScreen = false;
    S_GuiAddWidget(cont);
    
    plCurFrame = new cGuiWidgetLabel("LBL_PL_CUR_FRAME", "Frame: 1", 2, 3);
    plPlayPause = new cGuiWidgetButton("BTN_PL_PLAYPAUSE", "Play/Pause", 200, 1,
                                        true, cStormCallbacker(this, 
                                                &cStAnimGenerator::PlayPauseAnim)
                                        );
    cont->AddChild(new cGuiWidgetLabel("LBL_PLDRLOC", "Draw loc:", 2, 37));
    plLocX = new cGuiWidgetInput("INP_PL_LOCX", 85, 35, 60, 28, "400");
    plLocY = new cGuiWidgetInput("INP_PL_LOCY", 150, 35, 60, 28, "400");
    
    cont->AddChildren(4, plCurFrame, plPlayPause, plLocX, plLocY);
}
void cStAnimGenerator::InitGroupsWindow() {
    cGuiWidgetContainer *cont = new cGuiWidgetContainer("CONT_ANIM_GROUPS",
                                                "Frame groups",
                                                310, 20, 300, 250,
                                                true, false, false, false);
    S_GuiAddWidget(cont);
    
    gAnimStart = new cGuiWidgetInput("INP_GR_START", 1, 1, 45, 28);
    gAnimEnd = new cGuiWidgetInput("INP_GR_END", 48, 1, 45, 28);
    gAnimName = new cGuiWidgetInput("INP_GR_END", 94, 1, 140, 28);
    gAnimCreate = new cGuiWidgetButton("BTN_GR_CREATE", "Create", 236, 1, true,
                                        cStormCallbacker(this, 
                                            &cStAnimGenerator::CreateGroup)
                                        );
    gAnimList = new cGuiWidgetList("LS_GR_LIST", 1, 32, 299, 180, NULL);
    
    cont->AddChildren(5, gAnimStart, gAnimEnd, gAnimName, gAnimCreate, gAnimList);
}