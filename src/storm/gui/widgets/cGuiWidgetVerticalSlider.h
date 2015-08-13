//Created by Petar Ostojic
//Wed Apr  1 15:50:37 2015
#include "../cGuiWidget.h"

#ifndef CGUIWIDGETVERTICALSLIDER_H
#define CGUIWIDGETVERTICALSLIDER_H

class cGuiWidgetVerticalSlider : public cGuiWidget{
public:
	cGuiWidgetVerticalSlider(std::string _name, int x, int y, int h,
		int _minValue = 0, int _maxValue = 100, int _curValue = 1, bool _isEnabled = true);
	~cGuiWidgetVerticalSlider();

	int GetCurValue() { return curValue; }
	void SetCurValue(int value) { curValue = value; }
	void SetMaxValue(int value) { maxValue = value; }
	int GetMaxValue() { return maxValue; }

	void UpdatePosition(int newX, int newY);
	void HandleWidgetEvent(bool isMouseOver);
	void Render();
	void Draw();
private:
	int minValue;
	int maxValue;
	int curValue;
	bool isEnabled;
	int state;

	sRect borderTop, borderBottom;
	int sliderX, sliderY, sliderH;
	bool isSliding;
	bool canStartSlide;
	void CalculateSlider();		//Calculate slider position
};

#endif