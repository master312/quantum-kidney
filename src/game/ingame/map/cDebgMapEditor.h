/* 
 * File:   cDebgMapEditor.h
 * Author: master312
 *
 * Created on August 25, 2015, 8:43 PM
 */

#ifndef CDEBGMAPEDITOR_H
#define	CDEBGMAPEDITOR_H
#include <iostream>
#include "../../../storm/engine.h"
#include "../../../storm/gui/cGuiManager.h"
#include "../../sCommon.h"

class cDebgMapEditor {
public:
    cDebgMapEditor();
    ~cDebgMapEditor();
    
    /* Create simple map editor GUI, and console commands */
    void Init();
    
    /* Handle 'mapedit' console command */
    void CmdHandleMapEditor(void *data);
    /* Events handler */
    void HandleEvents(void *data);
    
    /* GUI callbacks */
    void ToggleTriggers(void *data);
    void PutBlock(void *data);
private:
    cGuiWidgetLabel *lblTool;
    bool isPutBlocks;
};

#endif	/* CDEBGMAPEDITOR_H */

