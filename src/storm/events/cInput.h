//Created by Petar Ostojic
//Tue Feb 24 00:55:00 2015
#include "../defines.h"
#include "../graphics/cGraphics.h"
#include "eKeys.h"
#include <map>
#include <vector>
#ifndef CINPUT_H
#define CINPUT_H
//DONE: Window resize event
//DONE: Dont ignore arrows, functions, backspace, escape, shift tab, and ctrl, keys while text input is enabled
//TODO: Key repeat interval
class cInput{
public:
	//Map of keys
	std::map<int, char> keys;
	//Mouse coordinates
	int mouseX;
	int mouseY;
	//True if mouse button is down; MOUSE_BUTTON_LEFT, MOUSE_BUTTON_RIGHT or MOUSE_BUTTON_MIDDLE
	bool mouseButton[3];
	int mouseScroll;
	//True, if quit signal is received
	bool toQuit;
	//True if manager is checking for text input, and not key events
	bool textScan;
	//This string contains text input from user
	std::string strText;
	//Pointer to graphics class
	cGraphics *graphics;
	//Was there new event, in this logic loop
	bool isNew;

	cInput(){
		mouseX = mouseY = 0;
		mouseButton[0] = mouseButton[1] = mouseButton[2] = false;
		mouseScroll = 0;
		graphics = NULL;
		toQuit = false;
		textScan = false;
		strText = "";
		isNew = false;
	}
	virtual ~cInput(){}
	//Handle key events
	//While returns true, there is new event. If returns false, there is no anymore events
	virtual bool Update() { return false; }

	//Sets pointer to graphics manager
	//If graphics manager is not set, window resize event will be ignoredф
	void SetGraphics(cGraphics *g){ graphics = g; }

	//Return true if key is pressed
	bool IsKeyDown(eKey key) { return keys[key] == 'd'; }
	//Return true if key is not pressed
	bool IsKeyUp(eKey key) { return keys[key] != 'd'; }
	//Return mouse coordinates
	int GetMouseX() { return mouseX; }
	int GetMouseY() { return mouseY; }

	bool IsMouseLeft() { return mouseButton[0]; }
	bool IsMouseRight() { return mouseButton[1]; }
	bool IsMouseMiddle() { return mouseButton[2]; }
	int GetMouseScroll() { int tmp = mouseScroll; mouseScroll = 0; return tmp; }

	//Reset all buttons to default state
	void ResetAll() { keys.clear(); }
	//Start scanning for text input
	void StartTextInput() { textScan = true; ResetAll(); strText = ""; }
	//Get text inputed
	std::string GetText() { return strText; }
	//Stop text input
	void StopTextInput() { textScan = false; }

	//Return true if program should be closed
	bool ToQuit() { return toQuit; }
};

#endif