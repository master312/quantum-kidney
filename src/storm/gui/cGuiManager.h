//Created by Petar Ostojic
//Wed Mar 18 00:04:53 2015
#include "../engine.h"
#include <iostream>
#include <map>
#include "../defines.h"
#include "cGuiSkin.h"
#include "cGuiWidget.h"
#include "widgets/cGuiWidgetContainer.h"
#include "widgets/cGuiWidgetCheckBox.h"
#include "widgets/cGuiWidgetButton.h"
#include "widgets/cGuiWidgetLabel.h"
#include "widgets/cGuiWidgetRadioGroup.h"
#include "widgets/cGuiWidgetInput.h"
#include "widgets/cGuiWidgetComboBox.h"
#include "widgets/cGuiWidgetHorizontalSlider.h"
#include "widgets/cGuiWidgetVerticalSlider.h"
#include "widgets/cGuiWidgetPictureBox.h"
#include "widgets/cGuiWidgetList.h"
#include "../cTimer.h"
//TODO: Show message bog
//TODO: Show blocking message box
#ifndef CGUIMANAGER_H
#define CGUIMANAGER_H

class cGuiManager{
public:
	cGuiManager();
	~cGuiManager();

	//Initialize gui manager
	bool Initialize();
	//Add new widget to manager
	//Returns widget id
	//This function will call widgets render function
	uint AddWidget(cGuiWidget *widget, cGuiSkin *skin = NULL);
	//Deletes widget object with matching ID from memory
	void Remove(uint id); 
	//Returns pointer to widget with matching id
	//Or NULL if not found
	cGuiWidget *GetWidget(uint id);
	//Returns pointer to widget with matching name
	//Or NULL if not found
        cGuiWidget *GetWidget(std::string name);
        //Show hidden widget matching ID
        void ShowWidget(uint id);
        //Show hidden widget matching name
        void ShowWidget(std::string name);
        //Hide widget matching ID
        void HideWidget(uint id);
        //Hide widget matching name
        void HideWidget(std::string name);
        
	void HandleEvents(void *data);
	void LogicTick();
	void GraphicsTick();
private:
	//Default skin
	//This skin will be used for widget, if none is specified
	cGuiSkin *defSkin;
	//Contains all widgets
	std::map<uint, cGuiWidget*> widgets;
	//Contains ID's of all widgets that are on screen
	std::vector<uint> onScreen;
	//Timer for logic ticking
	cTimer logicTimer;
};

#endif