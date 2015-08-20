//Created by Petar Ostojic
//Wed Mar 18 00:06:38 2015
#include "../engine.h"
#include "cGuiSkin.h"
#ifndef CGUIWIDGED_H
#define CGUIWIDGED_H
//TODO: Figure out how to handle child event...

class cGuiWidget{
public:
	int type;
	std::string name;
	cGuiSkin *skin;
	sRect loc;
	bool isOnScreen;
	//Value to be returned to gui manager from HandleEvents() function
	int toReturnEvent;

	cGuiWidget();
	virtual ~cGuiWidget();

	//Called from gui manager, to handle events for this widget
	//Return GUI_WIDGET_EVENT_...
	int HandleEvents();

	void SetLoc(int x, int y);
        //Adds multiple children to this widget
        void AddChildren(int count, ...);
	
	//Adds child to this widget
	virtual void AddChild(cGuiWidget *_child);
        //Return count of children that this widget have
	virtual int GetChildCount();
	//Return pointer to child
	virtual cGuiWidget *GetChild(int id);
	//Called when position of this widget is changed
	virtual void UpdatePosition(int newX, int newY);
	//Handle text input
	virtual void HandleText(bool isMouseOver);
	//Handle mouse motion
	virtual void HandleWidgetEvent(bool isMouseOver);
	//Logic tick. used for example in animated widgets
	virtual void LogicTick(); 
	virtual void Render();
	virtual void Draw();
};


#endif