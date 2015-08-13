//Created by Petar Ostojic
//Wed Mar 18 06:28:42 2015
#include "../cGuiWidget.h"
#ifndef CGUIWIDGETCHECKBOX_H
#define CGUIWIDGETCHECKBOX_H

class cGuiWidgetCheckBox : public cGuiWidget{
public:
	cGuiWidgetCheckBox(std::string _name, int x, int y, bool value, bool _isEnabled = true);
	cGuiWidgetCheckBox(std::string _name, std::string _label, int x, int y, 
			bool value, bool _isEnabled = true);
	~cGuiWidgetCheckBox();

	void SetVariable(bool *b) { isChecked = b; }
	//Returns pointer to value
	bool *GetValue() { return &isChecked; }
	void SetSide(bool s) { side = s; }

	void HandleWidgetEvent(bool isMouseOver);
	void UpdatePosition(int newX, int newY);
	void Render();
	void Draw();
private:
	bool isChecked;
	bool isEnabled;
	std::string label;
	int state;		//0-Normal;1-Over;2-Down;
	sRect labelLoc;	//Location of label, if any
	bool side;		//On what side of ch. box will text be writen; True = left
};


#endif