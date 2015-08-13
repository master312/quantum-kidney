//Created by Petar Ostojic
//Tue Mar 31 08:47:36 2015
#include "../cGuiWidget.h"
#ifndef CGUIWIDGETHORIZONTALSLIDER_H
#define CGUIWIDGETHORIZONTALSLIDER_H

class cGuiWidgetHorizontalSlider : public cGuiWidget{
public:
	cGuiWidgetHorizontalSlider(std::string _name, int x, int y, int w,
		int _minValue = 0, int _maxValue = 100, int _curValue = 1, bool _isEnabled = true);
	~cGuiWidgetHorizontalSlider();

	int GetCurValue() { return curValue; }
	void SetCurValue(int value) { curValue = value; }
	void SetMaxValue(int value) { maxValue = value; }
	int GetMaxValue() { return maxValue; }

	void HandleWidgetEvent(bool isMouseOver);
	void UpdatePosition(int newX, int newY);

	void Render();
	void Draw();

private:
	int minValue;
	int maxValue;
	int curValue;
	bool isEnabled;
	int state;

	sRect borderLeft, borderRight;
	int sliderX, sliderY, sliderW;
	bool isSliding;
	bool canStartSlide;

	void CalculateSlider();		//Calculate slider position
};

#endif