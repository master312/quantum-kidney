#include "cDebgMapEditor.h"
#include "cMapManager.h"

cDebgMapEditor::cDebgMapEditor() {
    isPutBlocks = false;
}
cDebgMapEditor::~cDebgMapEditor() {
}
void cDebgMapEditor::Init() {
    S_ConsoleAddHandler("mapedit", 
            cStormCallbacker(this, &cDebgMapEditor::CmdHandleMapEditor));
    S_AddEventHandler(
            new cStormCallbacker(this, &cDebgMapEditor::HandleEvents), 
            "cDebgMapEditor");
    
    cGuiWidgetContainer *cont = new cGuiWidgetContainer("CONT_MAPEDIT", 
                                                        "Debug map editor", 
                                                        100, 100, 300, 400, 
                                                        true, true, false, true);
    cont->isOnScreen = false;
    S_GuiAddWidget(cont);
    {
        lblTool = new cGuiWidgetLabel("LBL_CUR_M_EDIT_TOOL", "Tool: None", 1, 1);
        cont->AddChild(lblTool);
    
        cGuiWidgetButton *btn;
        btn = new cGuiWidgetButton("BTN_TGL_TRIGGERS", "Toggle triggers", 2, 23, true,
                    cStormCallbacker(this, &cDebgMapEditor::ToggleTriggers));
        cont->AddChild(btn);

        btn = new cGuiWidgetButton("BTN_TGL_BLOCK", "Put block", 2, 56, true,
                    cStormCallbacker(this, &cDebgMapEditor::PutBlock));
        cont->AddChild(btn);
    }
}
void cDebgMapEditor::CmdHandleMapEditor(void *data) {
    char **tmpData = (char**)data;
    if(tmpData[1] == NULL || (tmpData[1][0] != '0' && tmpData[1][0] != '1')){
        S_ConsolePrintLine("Command must be in format 'mapedit 1 or 0'");
        return;
    }
    
    if(tmpData[1][0] == '0'){
        S_ConsolePrintLine("Map editor hidden");
        S_GuiHideWidgetByName("CONT_MAPEDIT");
    }else if(tmpData[1][0] == '1'){
        S_ConsolePrintLine("Map editor shown");
        S_GuiShowWidgetByName("CONT_MAPEDIT");
    }
}
void cDebgMapEditor::HandleEvents(void *data) {
    if(isPutBlocks){
        if(S_IsMouseLeft()){
            GetCommon()->mapManager
                        ->SetTriggerScreen(S_GetMouseX(), S_GetMouseY(), -1);
        }else if(S_IsMouseRight()){
            GetCommon()->mapManager
                        ->SetTriggerScreen(S_GetMouseX(), S_GetMouseY(), 0);
        }
        return;
    }
}
//GUI callback methoods
void cDebgMapEditor::ToggleTriggers(void *data) {
    bool tmp = !GetCommon()->mapManager->GetIsDrawTriggerGrid();
    GetCommon()->mapManager->SetDrawTriggerGrid(tmp);
    
    if(!tmp){
        isPutBlocks = false;
        lblTool->SetText("Tool: None");
    }
}
void cDebgMapEditor::PutBlock(void *data) {
    isPutBlocks = !isPutBlocks;
    if(isPutBlocks){
        GetCommon()->mapManager->SetDrawTriggerGrid(true);
        lblTool->SetText("Tool: Put block");
    }else{
        lblTool->SetText("Tool: None");
    }
}