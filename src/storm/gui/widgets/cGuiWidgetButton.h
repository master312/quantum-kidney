//Created by Petar Ostojic
//Wed Mar 18 08:21:43 2015
#include "../cGuiWidget.h"
#include "../../cStormCallbacker.h"
#include <functional>
#ifndef CGUIWIDGETBUTTON_H
#define CGUIWIDGETBUTTON_H

class cGuiWidgetButton : public cGuiWidget{
public:
	cGuiWidgetButton(std::string _name, std::string _text, int x, int y, bool _isEnabled = true);
	cGuiWidgetButton(std::string _name, std::string _text, int x, int y, bool _isEnabled, 
		cStormCallbacker _callback);
	~cGuiWidgetButton();
	
	void SetCallBack(cStormCallbacker _callback);

	void UpdatePosition(int newX, int newY);
	void HandleWidgetEvent(bool isMouseOver);
	void Render();
	void Draw();
private:
	std::string text;
	bool isEnabled;
	int state;			//0-Nothing;1-Over;2-Donw

	sRect textLoc;
	sRect bLeft, bRight;
	sRect destRight;

	cStormCallbacker callback;
};

#endif