//Created by Petar Ostojic
//Fri Mar 20 02:53:45 2015
#include "../cGuiWidget.h"
#include <iostream>
#include "../../cTimer.h"
#ifndef CGUIWIDGETINPUT_H
#define CGUIWIDGETINPUT_H
//TODO: Unicode support!

class cGuiWidgetInput : public cGuiWidget{
public:
	cGuiWidgetInput(std::string _name, int x, int y, int w, int h, 
		std::string _text = "", bool _isEnabled = true);
	~cGuiWidgetInput();

	void UpdatePosition(int newX, int newY);
	void HandleText(bool isMouseOver);
	void HandleWidgetEvent(bool isMouseOver);
	void Render();
	void Draw();
        
        std::string GetText() { return text; }
        void SetText(std::string _text) { text = _text; visibleString = text; }
private:
	std::string text;
	//Is this input box enabled
	bool isEnabled;
	//Location of text pointer on screen
	//If this is equal to -1, then this input box is not selected
	int pointerLoc;
	//Is mouse over box
	bool isOver;
	//Locations of skin parts on screen
	sRect secMid, secLeft, secRight;

	sRect textRect;
	std::string visibleString;

	cTimer timer;

	void DrawSkin();
	void CalculateText();

	//Move text left or rigth; Left = true
	void Move(bool dir);
};


#endif