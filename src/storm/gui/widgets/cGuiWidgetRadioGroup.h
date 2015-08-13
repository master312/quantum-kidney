//Created by Petar Ostojic
//Thu Mar 19 16:45:24 2015
#include "../cGuiWidget.h"
#include <vector>
#ifndef CGUIWIDGETRADIOGROUP_H
#define CGUIWIDGETRADIOGROUP_H

class cGuiWidgetRadioGroup : public cGuiWidget{
public:
	cGuiWidgetRadioGroup(std::string _name, int x, int y, int w);
	cGuiWidgetRadioGroup(std::string _name, std::vector<std::string> _buttons, int x, int y, int w);
	~cGuiWidgetRadioGroup();

	void AddButton(std::string btn) { buttons.push_back(radioButton(btn)); }
	void SetValue(std::string btn, bool value);
	void SetEnabled(std::string btn, bool enabled);	
	int GetSelected() { return selected; }

	void HandleWidgetEvent(bool isMouseOver);
	void Render();
	void Draw();
private:
	struct radioButton{
		bool isEnabled;
		std::string text;
		radioButton(std::string _t){
			text = _t;
			isEnabled = true;
		}
	};
	static const int OFFSET = 3;
	//Id of button that is currently selected
	int selected;
	//Mouse is over widget with this ordinal is buttons vec,  or -1 if none
	int mouseOver;
	//Same as mouse over, just for mouse down
	int mouseDown;
	//Vector of all radio buttons
	std::vector<radioButton> buttons;
	//Dimensions of one radio box (circle :))
	sRect btnSize;
	//Temp rect used for button rendering
	sRect tmpRect;

	void DrawButton(int i);
};

#endif